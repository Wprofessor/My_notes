import numpy as  np


def loadDataSet():
    fr = open('C:\\Users\\王教授\\Desktop\\校赛D题\\test3.txt')
    dataset = []
    label = []
    for line in fr.readlines():
        line = line.strip().split()
        dataset.append(line[1:])
        label.append(line[0])
    return dataset, label


# 获取文档中出现的不重复词表
def createVocabList(dataset):
    vocaset = set([])  # 用集合结构得到不重复词表
    for document in dataset:
        vocaset = vocaset | set(document)  # 两个集合的并集
    return list(vocaset)


def setword(listvocaset, inputSet):
    newVocaset = [0] * len(listvocaset)
    for data in inputSet:
        if data in listvocaset:
            newVocaset[listvocaset.index(data)] = 1.0  # 如果文档中的单词在列表中，则列表对应索引元素变为1
    return newVocaset


# 欧式距离
def Euldist(listnewVocaset, label):
    fr = open('C:\\Users\\王教授\\Desktop\\aaa.txt')
    kinds = []
    kindData = []
    for line in fr.readlines():
        line = line.strip().split()
        kindData.append(line[1:])
        kinds.append(line[0])
    kindListnewVocaset = []
    for listvocaset in kindData:
        kindListnewVocaset.append(setword(vocaset, listvocaset))
    listnewVocaset = np.array(listnewVocaset)
    kindListnewVocaset = np.array(kindListnewVocaset)
    print(kindListnewVocaset)
    distMat = []
    for i in range(len(label)):
        temp = []
        for j in range(len(kinds)):
            diffMat = (listnewVocaset[j] - kindListnewVocaset[i]) ** 2
            temp.append(np.sum(diffMat) ** 0.5)
        distMat.append(temp)
    return distMat


def cosSimilarity(listnewVocaset, label):
    fr = open('C:\\Users\\王教授\\Desktop\\aaa.txt')
    kinds = []
    kindData = []
    for line in fr.readlines():
        line = line.strip().split()
        kindData.append(line[1:])
        kinds.append(line[0])
    kindListnewVocaset = []
    for listvocaset in kindData:
        kindListnewVocaset.append(setword(vocaset, listvocaset))
    listnewVocaset = np.array(listnewVocaset)
    kindListnewVocaset = np.array(kindListnewVocaset)
    distMat = []
    for i in range(len(label)):
        temp = []
        for j in range(len(kinds)):
            formatM = np.sum(listnewVocaset[j] * kindListnewVocaset[i])
            formatZ = (np.sum(listnewVocaset[j] ** 2) ** 0.5) * (np.sum(kindListnewVocaset[i] ** 2) ** 0.5)
            temp .append(formatM / formatZ)
        distMat.append(temp)
    return distMat


dataset, label = loadDataSet()
vocaset = createVocabList(dataset)
listnewVocaset = []
for listvocaset in dataset:
    listnewVocaset.append(setword(vocaset, listvocaset))
print('欧式距离：')
print(np.mat(Euldist(listnewVocaset, label)))
print('cos相似度：')
print(np.mat(cosSimilarity(listnewVocaset, label)))
