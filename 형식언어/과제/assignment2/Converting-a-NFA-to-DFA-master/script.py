from __future__ import generators
import json


with open('input.json') as i:
    j = json.load(i)
    
def powerset(s):
    
    if len(s) <= 1:
        yield s
        yield []
    else:
        for item in powerset(s[1:]):
            yield [s[0]]+item
            yield item

def Union(s,c,arr):
    q=[]
    for l in s:
        t = list(set().union(arr[n[c]][l],q))
        q = t
    return q

l = []
n = {}
t = []
for i in range(len(j["letters"])):
    n[j["letters"][i]] = i
for i in range(j["states"]):
    l.append(i)
r = [x for x in powerset(l)]
r.sort()
cols = j["states"]
rows = len(j["letters"])
arr = [[[] for i in range(cols)] for p in range(rows)] 
for d in j["t_func"]:
    a = n[d[1]]
    b = d[0]
    arr[a][b] = d[2]
for q in r:
    for c in j["letters"]:
        t.append([q,c,Union(q,c,arr)])
output = open("output.json",'w')    
o = {}
o["states"] = len(r)
o["letters"] = j["letters"]
o["t_func"] = t
o["start"] = [j["start"]]
k = []
b = []
match = False
for q in r:
    for l in q:
        for t in j["final"]:
            if l == t:
                k.append(list(q))
                match = True
                break
        if(match == True):
            match = False
            break                
o["final"] = k
json.dump(o,output, indent=2)