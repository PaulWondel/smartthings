import matplotlib.pyplot as plot
import csv

LEARNING_RATE = 0.0001
DELTA = 0.001

class Node:
    def __init__(self):
        self.inLinks = []
        self.value = None
    
    def __call__(self):
        if self.inLinks:
            self.value = sum([inLink() for inLink in self.inLinks])
        return self.value
    
class Link:
    def __init__(self, inNode = None, outNode = None):
        self.inNode = inNode
        outNode.inLinks.append(self)
        self.weight = 1.0
        self.gradient = 0.0
        
    def __call__(self):
        return self.weight * self.inNode()

    def adaptWeight(self):
        self.weight -= LEARNING_RATE * self.gradient

class Network:
    def __init__(self, numInputs, numOutputs):
        self.inNodes = [Node() for i in range(numInputs)]
        self.outNodes = [Node() for i in range(numOutputs)]

        self.links = []
        for inNode in self.inNodes:
            for outNode in self.outNodes:
                self.links.append(Link(inNode, outNode))

    def inference(self, x):
        for i in range(len(self.inNodes)):
            self.inNodes[i].value = x[i]
        self.y = [outNode() for outNode in self.outNodes]
        return self.y

    def loss(self, ycorrect):
        total = 0
        for i in range(len(self.y)):
            total += (self.y[i] - ycorrect[i]) * (self.y[i] - ycorrect[i])
        return total

    def computeAverageLoss(self, data):
        accumulatedLoss = 0
        for i in range(len(data[0])):
            self.inference(data[0][i])
            accumulatedLoss += self.loss([data[1][i]])
        return accumulatedLoss / len(data[0])
    
    def calculateGradients(self, data):
        self.averageLoss = self.computeAverageLoss(data)
        for link in self.links:
            link.weight += DELTA
            link.gradient = (self.computeAverageLoss(data) - self.averageLoss) / DELTA
            link.weight -= DELTA
    
    def adaptWeights(self):
        for link in self.links:
            link.adaptWeight()

    def gradientDescentOptimize(self, data):
        self.calculateGradients(data)
        self.adaptWeights()

def parseTime(time):
  hms = time.split(":")
  hms = list(map(int, hms))
  return hms[0] / 24 + hms[1] / 24 / 60 + hms[2] / 24 / 60 / 60

thermo_info = open('thermostaat.csv', newline='')
data = list(csv.reader(thermo_info))[1:] #skip the first column of every line
thermo_info.close()
# print(data)

inputs = [[parseTime(i[0]), float(i[1]), float(i[2]), 1] for i in data] # couple each input with a 1 as bias
outputs = [float(i[3]) for i in data]
testSet = [inputs, outputs]

network = Network(4, 1)

lossGraph = []
for i in range(200000):
    network.gradientDescentOptimize(testSet)
    if i % 10000 == 0:
        lossGraph.append([i, network.averageLoss])
        print ('Iteration:', i, '\nLoss:', network.averageLoss)
        for i, link in enumerate(network.links):
            print('Weight', i, ':', link.weight)

print(network.inference([40, 20, 1]))
plot.plot(*zip(*lossGraph))
plot.show()
