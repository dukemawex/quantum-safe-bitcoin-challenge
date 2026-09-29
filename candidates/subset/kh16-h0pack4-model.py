import random,json
from pathlib import Path
r=random.Random(1830);iv=[0x9b05688c,0x510e527f,0xbb67ae85,0x6a09e667];mask=0xffffffff
cases=[[[v]*4 for e in range(4)] for v in [0,1,255,256,0x7fffffff,0x80000000,0xffffffff]]
for e in range(4):
 for j in range(4):
  s=[[0]*4 for _ in range(4)];s[e][j]=0xffffffff;cases.append(s)
cases += [[[r.getrandbits(32) for j in range(4)] for e in range(4)] for _ in range(20000)]
for s in cases:
 a=[[(x+y)&mask for x,y in zip(row,iv)] for row in s];old=[row[3] for row in a];h01=[a[0][2],a[1][2],a[0][3],a[1][3]];h23=[a[2][2],a[3][2],a[2][3],a[3][3]];new=h01[2:]+h23[2:];assert old==new
 # Four quartets use the original 4*L addresses; flattening preserves the original key index.
assert [4*L+e for L in range(4) for e in range(4)]==list(range(16))
ns=list(range(1,33))+[40];nchecks=0
for n in ns:
 lim=0 if n>=32 else mask>>n;vs=[0,1,mask,0x7fffffff,0x80000000,lim,max(0,lim-1),min(mask,lim+1)]
 vs += [r.getrandbits(32) for _ in range(20000)]
 for h in vs:assert ((h>>(32-min(n,32)))==0)==(h<=lim)
 for bit in range(8):
  lane=[min(mask,lim+1)]*8;lane[bit]=0
  old=sum(int((x>>(32-min(n,32)))==0)<<i for i,x in enumerate(lane));new=sum(int(x<=lim)<<i for i,x in enumerate(lane));assert old==new==1<<bit
 nchecks+=len(vs)
result={'subset':{'identity_groups':len(cases),'four_final_states_per_group':True,'lane_order_exact':True,'target_execution':False},'pinning':{'word_predicate_checks':nchecks,'leading_bits':ns,'all_eight_mask_positions_checked':True,'target_execution':False}}
Path('/tmp/qsb-1830/model-results.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))
