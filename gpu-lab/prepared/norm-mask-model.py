from pathlib import Path
import random,json
R=random.Random(2016);B=1<<52;M=B-1;M48=(1<<48)-1;C=0x1000003d1;P=(1<<256)-C
limbs=lambda n:[(n>>(52*i))&M for i in range(5)]
def stage(v):
 t0,t1,t2,t3,t4=v;x=t4>>48;t4&=M48;t0+=x*C
 t1+=t0>>52;t0&=M;t2+=t1>>52;t1&=M;m=t1;t3+=t2>>52;t2&=M;m&=t2;t4+=t3>>52;t3&=M;m&=t3
 return [t0,t1,t2,t3,t4],m
def end(v,x):
 t0,t1,t2,t3,t4=v;t0+=(-x)&C;t1+=t0>>52;t0&=M;t2+=t1>>52;t1&=M;t3+=t2>>52;t2&=M;t4+=t3>>52;t3&=M;t4&=M48
 return [t0,t1,t2,t3,t4]
cases=[]
for bits in range(16):cases.append([limbs(P if (bits>>j)&1 else 1) for j in range(4)])
for v in [limbs(n) for n in [0,1,P-1,P,P+1,2*P-1,2*P,(1<<256)-1]]+[[0]*5,[(1<<62)-1]*5]:cases.append([v]*4)
cases += [[[R.randrange(1<<62) for _ in range(5)] for j in range(4)] for _ in range(20000)]
counts=[0,0]
for group in cases:
 ss=[stage(v) for v in group];mask=sum(int(t[0]>=0xffffefffffc2f and t[4]==M48 and m==M)<<j for j,(t,m) in enumerate(ss))
 for j,(v,(t,m)) in enumerate(zip(group,ss)):
  old=(t[4]>>48)|int(t[4]==M48 and m==M and t[0]>0xffffefffffc2e);new=(t[4]>>48)|((mask>>j)&1);assert old==new and old in [0,1]
  a=end(t,old);b=end(t,new);assert a==b;assert sum(z<<(52*i) for i,z in enumerate(a))==sum(z<<(52*i) for i,z in enumerate(v))%P;counts[old]+=1
result={'four_lane_groups':len(cases),'limb_vectors':len(cases)*4,'all_16_predicate_masks':True,'correction_counts':counts,'compared':'original and new canonical normalization and bigint mod p','target_execution':False};Path('/tmp/qsb-2016/normmask-model.json').write_text(json.dumps(result,indent=2)+'\n');print(result)
