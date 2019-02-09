# 文本分类器
import numpy as np


# 数据样本
def loadDataSet():
    dataset = [['my', 'dog', 'has', 'flea', 'problems', 'help', 'please'],
               ['maybe', 'not', 'take', 'him', 'to', 'dog', 'park', 'stupid'],
               ['my', 'dalmation', 'is', 'so', 'cute', 'I', 'love', 'hime'],
               ['stop', 'posting', 'stupid', 'worthless', 'garbage'],
               ['mr', 'licks', 'ate', 'my', 'steak', 'how', 'to', 'stop', 'him'],
               ['quit', 'buying', 'worthless', 'dog', 'food', 'stupid']]
    label = [0, 1, 0, 1, 0, 1]
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
            newVocaset[listvocaset.index(data)] = 1  # 如果文档中的单词在列表中，则列表对应索引元素变为1
    return newVocaset


def train(listnewVocaset, label):
    label = np.array(label)
    numDocument = len(listnewVocaset)  # 样本总数
    numWord = len(listnewVocaset[0])  # 词表的大小
    pInsult = np.sum(label) / float(numDocument)
    p0num = np.ones(numWord)  # 非侮辱词汇
    p1num = np.ones(numWord)  # 侮辱词汇
    p0Denom = 2.0       # 拉普拉斯平滑
    p1Denom = 2.0
    for i in range(numDocument):
        if label[i] == 1:
            p1num += listnewVocaset[i]
            p1Denom += 1
        else:
            p0num += listnewVocaset[i]
            p0Denom += 1
        p0 = p0num / p0Denom
        p1 = p1num / p1Denom
    return p0, p1, pInsult


dataset, label = loadDataSet()
voast = createVocabList(dataset)
listnewVocaset = []
for listvocaset in dataset:
    listnewVocaset.append(setword(voast, listvocaset))
print(train(listnewVocaset, label))
