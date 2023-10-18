import sys
import json
import itertools

unitStateEpsilonClosure = {}
visited = {}
nfaEpsilonClosureDict = {}

def computeNfaEpsilonClosureDict(nfaState,nfaTransitionMatrix):
    if visited[nfaState]:
        return nfaEpsilonClosureDict[nfaState]
    visited[nfaState]=True
    nfaEpsilonClosureDict[nfaState] = [nfaState]
    for arc in nfaTransitionMatrix:
        [ss, l, fs] = arc
        if (l != '$') or (ss != nfaState):
            continue
        children = computeNfaEpsilonClosureDict(fs,nfaTransitionMatrix)
        for child in children:
            if child not in nfaEpsilonClosureDict[nfaState]:
                nfaEpsilonClosureDict[nfaState].append(child)
    return nfaEpsilonClosureDict[nfaState]

def objectFA(s,l,tm,ss,fs):
    return {
        'states': s,
        'letters': l,
        'transition_matrix': tm,
        'start_states': ss,
        'final_states':fs
    }

def epsilonClosure(stateList):
    returnState = []
    for st in stateList:
        currentEpsilon = unitStateEpsilonClosure[st]
        for cst in currentEpsilon:
            if cst not in returnState:
                returnState.append(cst)
    return returnState

def allStatesCombination(nfaSTATES):
    return_state = []
    for i in range(len(nfaSTATES)+1):
        combination = [ list(tup) for tup in list(itertools.combinations(nfaSTATES,i))]
        return_state += combination
    return return_state

def getFinalState(nfaFinalStates,dfaStates):
    returnState = []
    for st in dfaStates:
        for fst in nfaFinalStates:
            if (st not in returnState)and(fst in st):
                returnState.append(st)
                break
    return returnState

def getTransitionedState(nfaTransitionMatrix, state, letter):
    ts = []
    for st in state:
        for arc in nfaTransitionMatrix:
            [ss, l, fs] = arc
            if (l != letter) or (ss != st):
                continue
            if fs not in ts:
                ts.append(fs)
    return ts

def formTransitionMatrix(nfaTransitionMatrix, dfaStates, dfaLetters):
    tm = []
    for st in dfaStates:
        for l in dfaLetters:
            transitionedState = getTransitionedState(nfaTransitionMatrix, st, l)
            tm.append([st,l,epsilonClosure(transitionedState)])
    return tm

def convertNFAToDFA(NFA):
    DFA_L = NFA['letters'][:]
    DFA_S = allStatesCombination(NFA['states'])
    DFA_S = sorted(DFA_S)
    DFA_FS = getFinalState(NFA['final_states'],DFA_S)
    
    for st in NFA['states']:
        for st1 in NFA['states']:
            visited[st1] = False
            nfaEpsilonClosureDict[st1]=[]
        unitStateEpsilonClosure[st] = computeNfaEpsilonClosureDict(st,NFA['transition_matrix'])

    DFA_SS = [ epsilonClosure([sst]) for sst in NFA['start_states'] ]
    DFA_TM = formTransitionMatrix(NFA['transition_matrix'], DFA_S, DFA_L)
    
    return objectFA(DFA_S,DFA_L,DFA_TM,DFA_SS,DFA_FS)


class MinimizeDFA():
    def __init__(self, rawDFA, output_file):
        self.output_file = output_file
        self.s = rawDFA['states']
        self.l = rawDFA['letters']
        self.tm = rawDFA['transition_matrix']
        self.ss = rawDFA['start_states']
        self.fs = rawDFA['final_states']
        for i in range(len(self.s)):
            self.s[i] = tuple(self.s[i])
        for i in range(len(self.ss)):
            self.ss[i] = tuple(self.ss[i])
        for i in range(len(self.fs)):
            self.fs[i] = tuple(self.fs[i])
        for i in range(len(self.tm)):
            for j in range(len(self.tm[i])):
                if isinstance(self.tm[i][j], list):
                    self.tm[i][j] = tuple(self.tm[i][j])


        self.nfs = []
        self.table = [ [ 0 for _ in range(len(self.s)) ] for _ in range(len(self.s)) ]
        self.__nonAcceptStates()
        self.__SIMAP()
        self.__LIMAP()
        self.deltaFunction = self.__makeDeltaFunction()
        self.__initializeTable()
        self.__updateTm()
        self.newStates = self.__updateStates()
        self.finalAcceptStates = self.__getFinalStates()
        self.finalStartStates = self.__getFinalStartStates()
        self.finalTm = self.__getFinalTm()
        self.__saveDFA()
    
    def __nonAcceptStates(self):
        for st in self.s:
            if st not in self.fs:
                self.nfs.append(st)
    
    def __SIMAP(self):
        state_index = {}
        index_state = {}
        for i in range(len(self.s)):
            state_index[self.s[i]] = i
            index_state[i] = self.s[i]
        self.siMap = state_index
        self.isMap = index_state

    def __LIMAP(self):
        letters_index = {}
        index_letters = {}
        for i in range(len(self.l)):
            letters_index[self.l[i]] = i
            index_letters[i] = self.l[i]
        self.liMap = letters_index
        self.ilMap = index_letters

    def __makeDeltaFunction(self):
        letterDict = []
        for _ in range(len(self.l)):
            letterDict.append("")
        deltaFunction = [ letterDict.copy() for _ in range(len(self.s)) ]
        for arc in self.tm:
            [ss, l, fs] = arc
            deltaFunction[self.siMap[ss]][self.liMap[l]] = fs
        return deltaFunction

    def __initializeTable(self):
        for i in range(len(self.table)):
            for j in range(len(self.table)):
                if self.isMap[i] in self.fs and self.isMap[j] in self.nfs or self.isMap[i] in self.nfs and self.isMap[j] in self.fs:
                        self.table[i][j] = 1
                if self.isMap[i] in self.fs and self.isMap[j] in self.nfs or self.isMap[i] in self.nfs and self.isMap[j] in self.fs:
                        self.table[j][i] = 1

    def __updateTm(self):
        while True:
            exitLoop = False
            lengthTm = len(self.table)
            for i in range(lengthTm):
                lengthTmi = len(self.table[i])
                for j in range(lengthTmi):
                    if i==j:
                        continue
                    else:
                        if not self.table[i][j]:
                            for k in self.l:
                                if len(self.deltaFunction[i][self.liMap[k]]) != 0:
                                    if len(self.deltaFunction[j][self.liMap[k]]) != 0:
                                        x = self.deltaFunction[i][self.liMap[k]] 
                                        y = self.deltaFunction[j][self.liMap[k]]
                                        x = tuple(sorted(x))
                                        y = tuple(sorted(y))
                                        if self.table[self.siMap[x]][self.siMap[y]]:
                                            self.table[i][j] = 1
                                            exitLoop = True
                                            break
            if not exitLoop:
                break
    
    def __updateStates(self):
        newStates = []
        lengthTm = len(self.table)
        for i in range(lengthTm):
            lengthTmi = len(self.table[i])
            for j in range(lengthTmi):
                if i==j:
                    continue
                else:
                    if not self.table[i][j]:
                        if len(newStates)==0:
                            newStates.append([self.isMap[i],self.isMap[j]])
                        elif len(newStates) > 0:
                            temp = False
                            lengthNewStates = len(newStates)
                            for k in range(lengthNewStates):
                                if self.isMap[i] in newStates[k] or self.isMap[j] in newStates[k]:
                                    newStates[k].append(self.isMap[i])
                                    newStates[k].append(self.isMap[j])
                                    newStates[k] = list(dict.fromkeys(newStates[k]))
                                    temp = True
                                    break
                            if temp == False:
                                newStates.append([self.isMap[i],self.isMap[j]])

        for state in self.s:
            appendVar = False
            for i in newStates:
                if state in i:
                    appendVar = True
                    break
            if appendVar == False:
                newStates.append([state])

        return newStates
    
    def __getFinalStates(self):
        final_states = []
        flag = False
        for i in self.newStates:
            for states in self.fs:
                if states in i:
                    final_states.append(i)
        
        return final_states

    def __getFinalStartStates(self):
        final_states = []
        for i in self.newStates:
            for states in self.ss:
                if states in i:
                    final_states.append(i)
                    break
        
        return final_states
    
    def __getFinalTm(self):
        finalTm = []
        for state in self.newStates:
            for letters in self.l:
                new = self.deltaFunction[self.siMap[state[0]]][self.liMap[letters]]
                for j in self.newStates:
                    if new in j:
                        new = j
                        break
                finalTm.append([state, letters, new])

        return finalTm

    def __saveDFA(self):
        newDFA = self.__objectDFA()
        with open(self.output_file, "w+") as outfile: 
            json.dump(newDFA, outfile, indent=4)

    def __objectDFA(self):
        return {
            'states': self.newStates,
            'letters': self.l,
            'transition_matrix': self.finalTm,
            'start_states': self.finalStartStates,
            'final_states':self.finalAcceptStates
        }
                         

try:
    with open("input.json", "r") as input_file: 
        rawNFA = json.load(input_file)
    s = rawNFA['states']
    l = rawNFA['letters']
    tm = rawNFA['transition_matrix']
    ss = rawNFA['start_states']
    fs = rawNFA['final_states']
    myNFA = objectFA(s, l, tm, ss, fs)
except:
    print("Error accessing `input_file`")
    quit()
    
finalDFA = convertNFAToDFA(myNFA)

try:
    output_file = 'output.json'
    rawDFA = finalDFA
except:
    print("error accessing `input_file` or `output file`")
    quit()
    
dfainstance = MinimizeDFA(rawDFA, output_file)