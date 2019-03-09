import numpy as np
import matplotlib.pyplot as plt


def loadDataSet(fileName):
    dataSet = []
    Labels = []
    fr = open(fileName)
    for line in fr.readlines():
        # 去掉换行符,默认逗号隔开
        lineArr = line.strip().split('\t')
        dataSet.append([float(lineArr[0]), float(lineArr[1])])
        Labels.append(lineArr[2])
    return dataSet, Labels


dataset, Labels = loadDataSet('./Data/svmtestset.txt')
dataset = np.mat(dataset)

# print(np.multiply(alpha, Labels))
# m, n = np.shape(dataset)
Labels = list(map(float, Labels))


# Labels = np.mat((Labels)).transpose()
# alpha = np.mat(np.zeros((m, 1)))
# front = np.multiply(alpha, Labels).T
# data = dataset * dataset[0, :].T
# print(front.shape)
# print(data.shape)
# print(data * front)
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
    # print(data_plus_np)
    # print(data_minus_np.transpose())


show(dataset, Labels)
