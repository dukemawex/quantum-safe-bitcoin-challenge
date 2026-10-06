#!/usr/bin/env python3
"""Minimal token-authenticated job agent for a rented GPU pod.

Outbound SSH is blocked from the controlling container, so the pod is driven
through the provider's HTTPS port proxy instead. Every request must carry
header `X-Token: $AGENT_TOKEN`.

  POST /exec          body = bash script   -> {"id": "<job>"}  (runs in background)
  GET  /job?id=ID&tail=N                   -> {"done", "rc", "log"}
  POST /put?path=P    body = file bytes    -> {"bytes": n}
  GET  /get?path=P                         -> file bytes
  GET  /health                             -> "ok" (no auth)
"""
import hmac, json, os, subprocess, threading, uuid
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import parse_qs, urlparse

TOKEN = os.environ["AGENT_TOKEN"]
JOBS = "/work/jobs"
os.makedirs(JOBS, exist_ok=True)
rcs = {}


def run_job(jid, script):
    log = open(f"{JOBS}/{jid}.log", "wb")
    p = subprocess.Popen(["bash", "-lc", script], stdout=log, stderr=subprocess.STDOUT, cwd="/work")
    rcs[jid] = None
    rcs[jid] = p.wait()
    log.close()


class H(BaseHTTPRequestHandler):
    def _send(self, code, body, ctype="application/json"):
        if isinstance(body, (dict, list)):
            body = json.dumps(body).encode()
        elif isinstance(body, str):
            body = body.encode()
        self.send_response(code)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def _authed(self):
        if hmac.compare_digest(self.headers.get("X-Token", ""), TOKEN):
            return True
        self._send(403, {"error": "forbidden"})
        return False

    def _body(self):
        return self.rfile.read(int(self.headers.get("Content-Length", "0")))

    def do_GET(self):
        u = urlparse(self.path); q = parse_qs(u.query)
        if u.path == "/health":
            return self._send(200, "ok", "text/plain")
        if not self._authed():
            return
        if u.path == "/job":
            jid = q["id"][0]
            path = f"{JOBS}/{jid}.log"
            if not os.path.exists(path):
                return self._send(404, {"error": "no such job"})
            data = open(path, "rb").read().decode(errors="replace")
            tail = int(q.get("tail", ["200"])[0])
            return self._send(200, {"done": rcs.get(jid) is not None, "rc": rcs.get(jid),
                                    "log": "\n".join(data.splitlines()[-tail:])})
        if u.path == "/get":
            path = q["path"][0]
            if not os.path.isfile(path):
                return self._send(404, {"error": "no such file"})
            return self._send(200, open(path, "rb").read(), "application/octet-stream")
        self._send(404, {"error": "not found"})

    def do_POST(self):
        u = urlparse(self.path); q = parse_qs(u.query)
        if not self._authed():
            return
        if u.path == "/exec":
            jid = uuid.uuid4().hex[:12]
            threading.Thread(target=run_job, args=(jid, self._body().decode()), daemon=True).start()
            return self._send(200, {"id": jid})
        if u.path == "/put":
            path = q["path"][0]
            os.makedirs(os.path.dirname(path) or ".", exist_ok=True)
            data = self._body()
            open(path, "wb").write(data)
            return self._send(200, {"bytes": len(data)})
        self._send(404, {"error": "not found"})

    def log_message(self, *a):
        pass


ThreadingHTTPServer(("0.0.0.0", 8000), H).serve_forever()
