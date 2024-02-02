from collections import Counter

celebrity_cipher = """WL  WG  SMBSNG  LYH  GSZH:  BCZHT

OHJHDP  LYHZGHMEHG  BWLY  AHBHMG

STJ  IKVG,  STJ  ZHT  BWLY  BWL  STJ

FKCLSLWCTG.” –ZSKVWDH  DYHESMWHV
"""
d = Counter()
for c in celebrity_cipher:
    if c in d:
        d[c] += 1
    else:
        d[c] = 1

print(d)

celebrity_cipher = """it  is  always  the  same:  women

bedeDP  themselves  with  Aewels

and  IKVs,  and  men  with  wit  and

FKotations.” –maKViDe  DhevalieV
"

