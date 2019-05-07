# 线性回归（标准方程法）
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def loadDataSet():
    fr = pd.read_excel('C:\\Users\\王教授\\Desktop\\校赛D题\\deal.xlsx')
    dataSet = []
    labels1 = []
    labels2 = []
    # fr.loc[x][y]:x表示列索引，y表示行索引
    # fr.loc[x]  :读取x这一列
    # 同理 fr.iloc[][] :按行读取
    for j in range(9):
        temp1 = []
        temp2 = []
        for i in range(12):
            if i % 2 == 0:
                temp1.append(fr.iloc[i][j])
            else:
                temp2.append(fr.iloc[i][j])
        labels1.append(temp1)
        labels2.append(temp2)
    for i in range(6):
        dataSet.append([1, i])
    return dataSet, labels2[3]


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


def predit(w, input):
    return input * w


def draw():
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
    plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
    dataSet, Labels = loadDataSet()
    plt.scatter([x[1] for x in dataSet], Labels)
    plt.plot([x[1] for x in dataSet], (np.mat(dataSet) * standRegres(dataSet, Labels)).T.tolist()[0])  # 矩阵转列表
    plt.xlabel('月份')  # 给 x 轴添加标签
    plt.ylabel('底价')  # 给 y 轴添加标签
    plt.title('18：57-20：25')
    plt.show()


dataSet, Labels = loadDataSet()
print(standRegres(dataSet, Labels))
for i in range(6, 9):
    print(np.array(predit(standRegres(dataSet, Labels), np.mat([1, i]))))
    # 计算出的w
draw()
# print(np.corrcoef(np.mat(Labels), (np.mat(dataSet) * standRegres(dataSet, Labels)).T))  # 计算相关系数
