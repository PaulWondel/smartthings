import matplotlib.pyplot as plot

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

x = [[84, 46], [73, 20], [65, 52], [70, 30], [76, 57], [69, 25], \
     [63, 28], [72, 36], [79, 57], [75, 44], [72, 24], [89, 31], \
     [65, 52], [57, 23], [59, 60], [69, 48], [60, 34], [79, 51], \
     [75, 50], [82, 34], [59, 46], [67, 23], [85, 37], [55, 40], \
     [63, 30]]
y = [354, 190, 405, 263, 451, 302, 288, 385, 402, 365, 209, 290, \
     346, 254, 395, 434, 220, 374, 308, 220, 311, 181, 274, 303, \
     244]
inputs = [i + [1] for i in x] # couple each input with a 1 as bias
testSet = [inputs, y]

network = Network(3, 1)

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
