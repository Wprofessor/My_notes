import numpy as np
import random


class opstruct:
    def __init__(self, dataSet, Labels, C, toler):
        self.X = dataSet
        self.LabelMat = Labels
        self.C = C
        self.tol = toler
        self.m = np.shape(dataSet)[0]
        self.alphas = np.mat(np.zeros((self.m, 1)))
        self.b = 0
        # 第一列标志E是否有效，第二列是实际E的值
        self.eCache = np.mat(np.zeros((self.m, 2)))

    # 计算E的值
    def calEk(oS, k):
        fXk = float(np.multiply(oS.alphas, oS.LabelMat).T * (oS.X * oS.X[k, :].T)) + oS.b
        Ek = fXk - float(oS.LabelMat[k])
        return Ek

    # 随机选择和第一个alpha不一样的另一个alpha下标
    # i:第一个alpha的下标；m：全部alpha的数量
    def selectA(i, m):
        j = i
        while i == j:
            j = int(random.uniform(0, m))
        return j

    # 启发式选择第二个a值
    # 寻找最大差值的Ej abs(Ei-Ej)
    def selectJ(oS, i, Ei):
        maxK = -1
        maxDelaE = 0
        Ej = 0
        oS.eCache[i] = [1, Ei]
        # 返回误差不为0的数据的索引值
        vaildEcacheList = np.nonzero(oS.eCache[:, 0].A)[0]
        if len(vaildEcacheList) > 1:
            for k in vaildEcacheList:
                if k == i:
                    continue
                Ek = oS.calEk(k)
                deltaE = abs(Ei - Ek)
                if deltaE > maxDelaE:
                    maxK = k
                    maxDelaE = deltaE
                    Ej = Ek
                return Ej
        else:
            j = oS.selectA(i, oS.m)
            Ej = oS.calEk(j)
        return j, Ej
