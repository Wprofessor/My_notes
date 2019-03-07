# 加载数据
import random


def loadDataSet(fileName):
    dataSet = []
    Labels = []
    fr = open(fileName)
    for line in fr.readline():
        # 去掉换行符
        lineArr = line.strip()
        # 默认逗号隔开
        lineArr = lineArr.split()
        dataSet.append([float(lineArr[0]), float(lineArr[1])])
        Labels.append(lineArr[2])
    return dataSet, Labels


# 随机选择和第一个alpha不一样的另一个alpha下标
# i:第一个alpha的下标；m：全部alpha的数量
def selectA(i, m):
    j = i
    while i == j:
        j = int(random.uniform(0, m))
    return j


# 用于调整alpha的值
# L:下限,H:上限
def judgeAlpha(aj, H, L):
    if aj > H:
        aj = H
    if aj < L:
        aj = L
    return aj


# 简化版smo优化算法
def smoSimple(dataSet, Labels, C, toler, maxIter):
    