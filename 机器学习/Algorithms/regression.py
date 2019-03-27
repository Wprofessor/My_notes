# 线性回归（标准方程法）
import numpy as np
import matplotlib.pyplot as plt


def loadDataSet(filename):
    # numFeat = len(open(filename).readline().split())
    dataSet = []
    Labels = []
    for line in open(filename).readlines():
        dataSet.append([float(line.split()[0]), float(line.split()[1])])
        Labels.append(float(line.split()[-1]))
    return dataSet, Labels


def standRegres(xArr, yArr):
    xMat = np.mat(xArr)
    yMat = np.mat(yArr).T  # 先转换成n行一列
    temp = (xMat.T * xMat)
    if np.linalg.det(temp) == 0.0:  # 判断行列式是否为0
        print("行列式为0，无法计算")
        return
    else:
        w = temp.I * xMat.T * yMat
    return w


def draw():
    dataSet, Labels = loadDataSet("./Data/ex0.txt")
    plt.scatter([x[1] for x in dataSet], Labels)
    plt.plot([x[1] for x in dataSet], (np.mat(dataSet) * standRegres(dataSet, Labels)).T.tolist()[0])  # 矩阵转列表
    plt.show()


dataSet, Labels = loadDataSet("./Data/ex0.txt")
print(standRegres(dataSet, Labels))
# 计算出的w
draw()
print(np.corrcoef(np.mat(Labels), (np.mat(dataSet) * standRegres(dataSet, Labels)).T))  # 计算相关系数
