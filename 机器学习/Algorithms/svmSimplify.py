# 加载数据
import random
import numpy as np
import matplotlib.pyplot as plt


def loadDataSet(fileName):
    dataSet = []
    Labels = []
    fr = open(fileName)
    for line in fr.readlines():
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


def show(dataSet, Labels):
    # 正样本
    data_plus = []
    # 负样本
    data_minus = []
    for i in range(len(dataSet)):
        if Labels[i] > 0:
            data_plus.append(dataSet[i])
        else:
            data_minus.append(dataSet[i])
        data_plus_np = np.array(data_plus)
        data_minus_np = np.array(data_minus)
        plt.scatter(np.transpose(data_plus_np)[0], np.transpose(data_plus_np)[1])
        plt.scatter(np.transpose(data_minus_np)[0], np.transpose(data_minus_np)[1])
        plt.show()


# 简化版smo优化算法
def smoSimple(dataSet, Labels, C, toler, maxIter):
    # mat意思为转换为矩阵
    dataSet = np.mat(np.array(dataSet))
    # transpose意思为矩阵的转置
    Labels = np.mat(np.array(Labels)).transpose()
    b = 0
    m, n = np.shape(dataSet)
    # 初始化alpha
    alphas = np.mat(np.zeros((m, 1)))
    # 记录alpha不改变时遍历的次数
    iter = 0
    while iter < maxIter:
        # 记录alpha是否被优化
        alphaChanged = 0
        for i in range(m):
            # 计算Ei
            fxi = float(np.multiply(alphas, Labels).T * (dataSet * dataSet[i, :].T)) + b
            Ei = fxi - float(Labels[i])
            if (Labels[i] * Ei < -toler) and (alphas[i] < C) or (Labels[i] * Ei > toler) and (alphas[i] > 0):
                # 选取另一个alpha
                j = selectA(i, m)
                fxj = float(np.multiply(alphas, Labels).T * (dataSet * dataSet[j, :].T)) + b
                Ej = fxj - float(Labels[j])
                # copy()和直接赋值=的区别
                # a=[0,1,2,3,4,5]
                # b=a
                # c=a.copy()
                #
                # del a[1]
                # '''
                #    各变量值为：
                #    a=[0, 2, 3, 4, 5]
                #    b=[0, 2, 3, 4, 5]
                #    c=[0, 1, 2, 3, 4, 5]
                # '''
                #
                # b.remove(4)
                # '''
                #    各变量值为：
                #    a=[0, 2, 3, 5]
                #    b=[0, 2, 3, 5]
                #    c=[0, 1, 2, 3, 4, 5]
                # '''
                #
                # c.append(9)
                # '''
                #    各变量值为：
                #    a=[0, 2, 3, 5]
                #    b=[0, 2, 3, 5]
                #    c=[0, 1, 2, 3, 4, 5, 9]
                # '''
                alphaIold = alphas[i].copy()
                alphaJold = alphas[j].copy()
                # 计算上界和下界
                if Labels[i] != Labels[j]:
                    L = max(0, alphas[j] - alphas[i])
                    H = min(C, C + alphas[j] - alphas[i])
                else:
                    L = max(C, alphas[i] + alphas[j] - C)
                    H = min(C, alphas[i] + alphas[j])
                if L == H:
                    print("L == H")
                    # 本次循环结束，直接开始下次循环
                    continue
                # 计算分母2K(x1,x2) - K(x1,x1)-K(x2,x2)
                eta = 2.0 * (dataSet[i, :] * dataSet[j, :].T) - \
                      dataSet[i, :] * dataSet[i, :].T - dataSet[j, :] * dataSet[j, :].T

                # 因为a初始值为0，所以此条件是防止a过小的一个优化操作
                if eta >= 0:
                    print("eta >= 0")
                    continue
                # 修改a2
                alphas[j] -= Labels[j] * (Ei - Ej) / eta
                # 修剪a2
                alphas[j] = judgeAlpha(alphas[j], H, L)
                if abs(alphaJold - alphas[j]) < 0.5:
                    print("更新的太小了")
                    continue
                # 更新a1
                alphas[i] += (Labels[i] * Labels[j]) * (alphaJold - alphas[j])
                # 计算b1
                b1 = b - Ei - Labels[i] * (dataSet[i, :] * dataSet[i, :].T) * (alphas[i] - alphaIold) - \
                     Labels[j] * (dataSet[j, :] * dataSet[i, :].T) * (alphas[j] - alphaJold)
                # 计算b2
                b2 = b - Ej - Labels[i] * (dataSet[i, :] * dataSet[j, :].T) * (alphas[i] - alphaIold) - \
                     Labels[j] * (dataSet[j, :] * dataSet[j, :].T) * (alphas[j] - alphaJold)
                # 选取合适的b
                if alphas[i] > 0 and alphas[i] < C:
                    b = b1
                elif alphas[j] > 0 and alphas[j] < C:
                    b = b2
                else:
                    b = (b1 + b2) / 2.0
                alphaChanged += 1
                print("第%d次迭代 样本:%d, alpha优化次数:%d" % (iter, i, alphaChanged))

        if alphaChanged == 0:
            iter += 1
        else:
            iter = 0
        print("迭代次数:----------------------------------------------", iter)
    return b, alphas


dataSet, Labels = loadDataSet('./Data/svmtestset.txt')
Labels = list(map(float, Labels))
b, alphas = smoSimple(dataSet, Labels, 0.6, 0.001, 40)
show(dataSet, Labels)
