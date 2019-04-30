# 贝叶斯处理多分类问题
import numpy as np


# 数据样本
def loadDataSet():
    # fr = open('C:\\Users\\王教授\\Desktop\\test.txt')
    # dataset = []
    #
    # for line in fr.readlines():
    #     line = line.strip()
    #     temp = []
    #     for i in range(len(str(line))):
    #         temp.append(line[i])
    #     dataset.append(temp)
    # fr = open('C:\\Users\\王教授\\Desktop\\test1.txt')
    # dataset = []
    #
    # for line in fr.readlines():
    #     line = line.strip()
    #     temp = line.split(',')
    #     dataset.append(temp)
    # label = [1, 2, 3, 4, 5, 6]
    fr = open('C:\\Users\\王教授\\Desktop\\test2.txt')
    dataset = []
    label = []
    for line in fr.readlines():
        line = line.strip().split()
        dataset.append(line[1:-1])
        label.append(int(line[-1]))
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
    pInsult = 1.0 / 6.0
    p1num = np.ones(numWord)
    p2num = np.ones(numWord)
    p3num = np.ones(numWord)
    p4num = np.ones(numWord)
    p5num = np.ones(numWord)
    p6num = np.ones(numWord)
    p1Denom = 2.0  # 拉普拉斯平滑
    p2Denom = 2.0
    p3Denom = 2.0
    p4Denom = 2.0
    p5Denom = 2.0
    p6Denom = 2.0
    for i in range(numDocument):
        if label[i] == 1:
            p1num += listnewVocaset[i]
            p1Denom += 1
        elif label[i] == 2:
            p2num += listnewVocaset[i]
            p2Denom += 1
        elif label[i] == 3:
            p3num += listnewVocaset[i]
            p3Denom += 1
        elif label[i] == 4:
            p4num += listnewVocaset[i]
            p4Denom += 1
        elif label[i] == 5:
            p5num += listnewVocaset[i]
            p5Denom += 1
        elif label[i] == 6:
            p6num += listnewVocaset[i]
            p6Denom += 1
        # 取对数是为了防止因为小数连乘而造成向下溢出
        p1 = np.log(p1num / p1Denom)
        p2 = np.log(p2num / p2Denom)
        p3 = np.log(p3num / p3Denom)
        p4 = np.log(p4num / p4Denom)
        p5 = np.log(p5num / p5Denom)
        p6 = np.log(p6num / p6Denom)
    return p1, p2, p3, p4, p5, p6, pInsult


# 分类函数
def classiyyNB(Inputdata, p1, p2, p3, p4, p5, p6, pInsult):
    # 因为取对数，因此连乘操作就变成了连续相加
    p1vec = np.sum(Inputdata * p1) + np.log(pInsult)
    p2vec = np.sum(Inputdata * p2) + np.log(pInsult)
    p3vec = np.sum(Inputdata * p3) + np.log(pInsult)
    p4vec = np.sum(Inputdata * p4) + np.log(pInsult)
    p5vec = np.sum(Inputdata * p5) + np.log(pInsult)
    p6vec = np.sum(Inputdata * p6) + np.log(pInsult)
    save = []
    save.append(p1vec)
    save.append(p2vec)
    save.append(p3vec)
    save.append(p4vec)
    save.append(p5vec)
    save.append(p6vec)
    t = save.index(max(save))
    return t + 1


def testingNB():
    dataset, label = loadDataSet()
    voast = createVocabList(dataset)
    # 去掉多余的空格
    for i in range(len(voast)):
        voast[i] = str(voast[i]).strip()
    listnewVocaset = []
    for listvocaset in dataset:
        listnewVocaset.append(setword(voast, listvocaset))
    p1, p2, p3, p4, p5, p6, pInsult = train(listnewVocaset, label)
    fr = open('C:\\Users\\王教授\\Desktop\\preditData.txt')
    Inputdata = []
    kinds = []
    for line in fr.readlines():
        line = line.strip().split()
        kinds.append(str(line[0]))
        Inputdata.append(line[1:])
    Inputdata = np.array(Inputdata)
    for i in range(len(kinds)):
        temp = setword(voast, Inputdata[i])
        print('”', kinds[i], "”对应的分类是：",classiyyNB(temp, p1, p2, p3, p4, p5, p6, pInsult))

testingNB()
