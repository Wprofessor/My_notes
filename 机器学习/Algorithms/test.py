from numpy.random import RandomState
import tensorflow as tf
import numpy as np
import pandas as pd

fr = pd.read_excel('C:\\Users\\王教授\\Desktop\\deal.xlsx')
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

print(np.mat(labels1))
print(labels2)
print(np.mat(dataSet).shape)
