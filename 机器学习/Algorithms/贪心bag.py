import numpy as np


class Bag:
    def __init__(self):
        self.w = []  # 重量
        self.v = []  # 价值
        self.Wv = []
        print('请输入物品数量：')
        self.n = int(input())
        print('请输入背包容量：')
        self.m = int(input())
        for i in range(self.n):
            print('请输入每个物品的重量和价值：')
            x = int(input())
            y = int(input())
            self.w.append(x)
            self.v.append(y)
        self.w = np.array(self.w)
        self.v = np.array(self.v)
        self.Wv = np.array(self.Wv)
        self.Wv = self.w / self.v
        np.argsort(self.Wv)

    def GreedSack(self):
        sum = 0.0
        weight = self.m
        tag = 0.0
        for i in range(self.n - 1, -1, -1):
            j = int(self.Wv[i])
            weight = weight - self.w[j]
            if weight < 0:
                weight += self.w[j]
                tag = j
                break
            sum += self.v[j]
            print(weight)
        sum += weight * (self.v[tag] / self.w[tag])
        return sum


if __name__ == '__main__':
    t = Bag()
    print(t.GreedSack())
