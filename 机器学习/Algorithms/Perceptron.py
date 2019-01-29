import random
import numpy as np
import matplotlib.pyplot as plt


class percePtron:
    def __init__(self):
        self.weight = [0, 0]
        self.bias = 0

    def draw(self, x1, x2, y1, y2):
        plt.scatter(x1, y1, label="y = 1")
        plt.scatter(x2, y2, label="y = -1")
        plt.legend()
        plt.xlabel('X1')
        plt.ylabel('X2')
        label_x = np.linspace(0, 4, 20)
       # print(-(self.bias + self.weight[0] * label_x) / self.weight[1])
        plt.plot(label_x, -(self.bias + self.weight[0] * label_x) / self.weight[1])
        plt.show()

    def train(self, data, learning_rate=0.5, step=100):
        self.weight = np.array(self.weight)
        for i in range(step):
            randomindex = random.randint(0,len(data)-1)
            randomData = data[randomindex]
            if randomData[2] * (self.weight[0] * randomData[0] + self.weight[1] * randomData[1] + self.bias) < 0:
                self.weight[0] = (self.weight[0] + randomData[0]) * learning_rate
                self.weight[1] = (self.weight[1] + randomData[1]) * learning_rate
                self.bias = (self.bias + randomData[2]) * learning_rate
                print('weight', self.weight)
                print('bias', self.bias)


if __name__ == "__main__":
    data = [[1, 4, 1], [0.5, 2, 1], [2, 2.3, 1], [1, 0.5, -1], [2, 1, -1],
            [4, 1, -1], [3.5, 4, 1], [3, 2.2, -1]]
    x1 = []
    y1 = []
    x2 = []
    y2 = []
    for p in data:
        if p[2] > 0:
            x1.append(p[0])
            y1.append(p[1])
        else:
            x2.append(p[0])
            y2.append(p[1])
    x1 = np.array(x1)
    x2 = np.array(x2)
    y1 = np.array(y1)
    y2 = np.array(y2)
    # plt.scatter(x1, y1, label="y = 1")
    # plt.scatter(x2, y2, label="y = -1")
    # plt.legend()
    # plt.xlabel('X1')
    # plt.ylabel('X2')
    # plt.show()
    model = percePtron()
    model.train(data)
    model.draw(x1, x2, y1, y2)

