from itertools import combinations
import sys

class Apriori:
    def __init__(self, inputfile,minSupport=0.5, minConfidence=0.7):
        self.transactions = []
        self.itemSet = set([])
        self.allLSetDict = {}
        self.rules = []
        self.readFile(inputfile)
        self.calcLSet(minSupport)
        self.calcAssociationRules(minConfidence)
        self.printResult()

    def calcSupport(self, itemlist):
        if type(itemlist) != set:
            itemlist = set(itemlist)
        return len(list(filter(lambda transaction: itemlist.issubset(transaction), self.transactions)))/len(self.transactions)

    def calcLSet(self, minSupport):
        curCSet = self.itemSet
        numOfItems = 1
        curLSetWithSupport = []
        allLSetsWithSupport = []
        while len(curCSet)>0:
            if(numOfItems>1): # curLSet has to be frozeset, otherwise it can't be instantiated as a set
                curCSet = set([i[0].union(j[0]) for i in curLSetWithSupport for j in curLSetWithSupport if len(i[0].union(j[0]))==numOfItems])
            curCSetWithSupport = list(map(lambda item: (frozenset(item), self.calcSupport(item)), curCSet))
            curLSetWithSupport = list(filter(lambda cset: cset[1]>=minSupport,curCSetWithSupport))
            allLSetsWithSupport.extend(curLSetWithSupport)
            numOfItems += 1
        
        for key,val in allLSetsWithSupport:
            self.allLSetDict[key] = val

    def calcAssociationRules(self, minConfidence):
        for key in self.allLSetDict:
            subsets = [frozenset(item) for i in range(1, len(key)) for item in combinations(key, i)]
            for subset in subsets:
                confidence = self.allLSetDict[key]/self.allLSetDict[subset]
                if confidence >= minConfidence:
                    self.rules.append([subset,key-subset,confidence])

    def printResult(self):
        print('Transactions:')
        for transaction in self.transactions:
            print(transaction)
        print('Association Rules:')
        for rule in self.rules:
            print('{0}=>{1}'.format(list(rule[0]), list(rule[1])))

    def readFile(self, inputfile):
        inputFile = open(inputfile, 'r')
        for line in inputFile.readlines():
            items = set(line.strip().split(','))
            if len(items)>0:
                self.transactions.append(items)
                for item in items:
                    self.itemSet.add(frozenset([item]))
        inputFile.close()

minSupport=float(sys.argv[2])
minConfidence=float(sys.argv[3])
print('Database with min support {0} and min confidence {1}'.format(minSupport,minConfidence))
apriori = Apriori(sys.argv[1],minSupport,minConfidence)
