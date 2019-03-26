# 线性回归（标准方程法）
import numpy as np


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
    yMat = np.mat(yArr).T   # 先转换成n行一列
    temp = (xMat.T * xMat)
    if np.linalg.det(temp) == 0.0:  # 判断行列式是否为0
        print("行列式为0，无法计算")
        return
    else:
        w = temp.I * xMat.T * yMat
    return w


dataSet, Labels = loadDataSet("./Data/ex0.txt")
print(standRegres(dataSet, Labels))
