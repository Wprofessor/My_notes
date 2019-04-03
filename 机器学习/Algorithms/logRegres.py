import numpy as np
import matplotlib.pyplot as plt


def loadDataSet():
    dataMat = []
    LabelMat = []
    fr = open("./Data/logRegresTestSet.txt")
    for line in fr.readlines():
        # split是分割函数，将数据以字符串的形式保存在列表中
        line = line.strip().split()
        dataMat.append([1.0, float(line[0]), float(line[1])])
        LabelMat.append(float(line[-1]))
    return dataMat, LabelMat


# 辅助函数
def signed(x):
    return 1.0 / (1 + np.exp(-x))


# 批处理
def gradAscent(dataMat, LabelMat):
    data = np.mat(dataMat)
    labels = np.mat(LabelMat).T
    m, n = np.shape(data)
    weights = np.mat(np.zeros((n, 1)))
    for i in range(500):
        h = signed(data * weights)
        error = labels - h
        weights = weights + data.T * error
    return weights


# 随机梯度(每次仅用一个样本点更新回归系数)
def stocGradAscent(dataMat, LabelMat):
    dataMat = np.array(dataMat)
    LabelMat = np.array(LabelMat)
    m, n = np.shape(dataMat)
    weights = np.ones(n)
    for i in range(3000):
        randIndex = np.random.randint(0, m)
        h = signed(np.sum(dataMat[randIndex] * weights))
        error = LabelMat[randIndex] - h
        weights = weights + error * dataMat[randIndex]
    return weights

def draw(weights):
    weights = np.array(weights)
    dataMat, LabelMat = loadDataSet()
    dataMat = np.array(dataMat)
    LabelMat = np.array(LabelMat)
    xMat1 = []
    yMat1 = []
    xMat2 = []
    yMat2 = []
    for i in range(len(LabelMat)):
        if LabelMat[i] == 1:
            xMat1.append(dataMat[i][1])
            yMat1.append(dataMat[i][2])
        else:
            xMat2.append(dataMat[i][1])
            yMat2.append(dataMat[i][2])
    x1 = dataMat[:, 1]
    x2 = dataMat[:, 2]
    x = np.linspace(np.min(x1), np.max(x2), len(LabelMat))
    y = (-weights[0] - weights[1] * x) / weights[2]
    plt.scatter(xMat1, yMat1)
    plt.scatter(xMat2, yMat2)
    plt.plot(x, y, "r")
    plt.show()


dataMat, LabelMat = loadDataSet()
print(gradAscent(dataMat, LabelMat))
# draw(gradAscent(dataMat, LabelMat))
draw(stocGradAscent(dataMat, LabelMat))
