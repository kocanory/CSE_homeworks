Requirements
------------

1.Python3

2.Json module

3.Future module

Assumptions 
-----------

1.  The input file name should be “input.json”.The input.json file should contain an object which represents a NFA. This json object
will have 5 key-value pairs corresponding to the 5-tuple used to represent the
NFA.

Code snippets 
-------------


    with open('input.json') as i:
        j = json.load(i)

Here the file is opened and assigned to a variable “j”.

    def powerset(s):
        
        if len(s) <= 1:
            yield s
            yield []
        else:
            for item in powerset(s[1:]):
                yield [s[0]]+item
                yield item

Here we define a function which gives us the powerset of a set given in the arguement.


    def Union(s,c,arr):
        q=[]
        for l in s:
            t = list(set().union(arr[n[c]][l],q))
            q = t
        return q

Now here we define a function called “Union” which returns a list of union a sets given through the arguements.

    for i in range(len(j["letters"])):
        n[j["letters"][i]] = i
    for i in range(j["states"]):
        l.append(i)

Here in the first two lines, we map the letters to numbers and in the second two lines, we made a copy of states.

    r = [x for x in powerset(l)]
    r.sort()

Here we make a powerset of the given input states and sort it.

    cols = j["states"]
    rows = len(j["letters"])
    arr = [[[] for i in range(cols)] for p in range(rows)] 
    for d in j["t_func"]:
        a = n[d[1]]
        b = d[0]
        arr[a][b] = d[2]

Now, we make a 2D array a make a transition table(all transition function values).

    for q in r:
        for c in j["letters"]:
            t.append([q,c,Union(q,c,arr)])

Here we use the Union function to make the transition function for output DFA.

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

Here we make a list of union of sets where atleast an element of the set is present in input NFA’s final states.

    output = open("output.json",'w')
    o["states"] = len(r)
    o["letters"] = j["letters"]
    o["t_func"] = t
    o["start"] = [j["start"]]
    o["final"] = k
    json.dump(o,output, indent=2)

At last, we open the output file and and dump the json “o” to the output file “output.json”.

