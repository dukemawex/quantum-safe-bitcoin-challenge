import random,json
from pathlib import Path
rng=random.Random(20260929);M=2**32-1;IV=[0x9b05688c,0x510e527f,0xbb67ae85,0x6a09e667]
cases=[]
for v in [0,1,M,M-IV[3],M-IV[3]+1,0x80000000]:cases.append([[v]*4 for _ in range(16)])
for i in range(16):
 st=[[0]*4 for _ in range(16)];st[i][3]=(-IV[3])&M;cases.append(st)
for _ in range(20000):cases.append([[rng.getrandbits(32) for _ in range(4)] for i in range(16)])
for states in cases:
 old=[];raw=[]
 for L in range(4):
  for e in range(4):
   S0=states[4*L+e]
   old.append([(x+y)&M for x,y in zip(S0,IV)][3]);raw.append(S0[3])
 new=[(x+IV[3])&M for x in raw]
 assert old==new
 for z in [1,8,16,24,31,32,40]:
  oldmask=sum((v < (1 << (32-min(z,32)))) << i for i,v in enumerate(old))
  newmask=sum((int((v >> (32-min(z,32)))==0)) << i for i,v in enumerate(new))
  assert oldmask==newmask
out={'groups':len(cases),'four_word_states_per_group':16,'zero_bit_cases':[1,8,16,24,31,32,40],'all_16_key_mask_positions':True,'native_simd_execution':False,'full_sha_digest_execution':False,'scope':'full-register IV addition then lane3 extraction vs sixteen extracted lanes plus broadcast IV A; ordering, modulo32 wrapping, pass masks'}
Path('/tmp/qsb-0758/kh16add-model.json').write_text(json.dumps(out,indent=2)+'\n');print(out)
