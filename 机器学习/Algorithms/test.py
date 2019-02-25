import numpy as np
from os import listdir  # listdir可以列出给定目录的文件名


def imgVector(filename):
    resultVector = np.zeros((1, 1024))
    fr = open(filename)
    for i in range(32):
        lineStr = fr.readline()
        for j in range(32):
            resultVector[0, 32 * i + j] = int(lineStr[j])
    return resultVector


def handwritingTest():
    handLabels = []
    handDigitsList = listdir('./Data/handDigits/')  # 返回的是列表对象
    num = len(handDigitsList)
    trainDataset = np.zeros((num, 1024))
    for i in range(5):
        handLabels.append(int(handDigitsList[i][0]))
        trainDataset[i, :] = imgVector('./Data/handDigits/' + handDigitsList[i])

    print(trainDataset)


# test = imgVector('./Data/testtest.txt')
#
# val = np.zeros((3, 1024))
#
# val[0] = test
# print(val)
# print(test)
# #print(test[0])

handwritingTest()
