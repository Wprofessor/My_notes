# 文本分类器
import numpy as np


# 数据样本
def loadDataSet():
    # dataset = [['my', 'dog', 'has', 'flea', 'problems', 'help', 'please'],
    #     #            ['maybe', 'not', 'take', 'him', 'to', 'dog', 'park', 'stupid'],
    #     #            ['my', 'dalmation', 'is', 'so', 'cute', 'I', 'love', 'hime'],
    #     #            ['stop', 'posting', 'stupid', 'worthless', 'garbage'],
    #     #            ['mr', 'licks', 'ate', 'my', 'steak', 'how', 'to', 'stop', 'him'],
    #     #            ['quit', 'buying', 'worthless', 'dog', 'food', 'stupid']]
    dataset = [['玩', '游', '戏', '吧'],
               ['玩', 'lol', '吧'],
               ['我', '要', '学', '习'],
               ['学', '习', '使', '我', '快', '了'],
               ['学', '习', '万', '岁'],
               ['我', '要', '玩', '耍']]
    label = [1, 1, 0, 0, 0, 1]
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
    p0Denom = 2.0  # 拉普拉斯平滑
    p1Denom = 2.0
    for i in range(numDocument):
        if label[i] == 1:
            p1num += listnewVocaset[i]
            p1Denom += 1
        else:
            p0num += listnewVocaset[i]
            p0Denom += 1
        # 取对数是为了防止因为小数连乘而造成向下溢出
        p0 = np.log(p0num / p0Denom)  # 属于非侮辱性文档的概率
        p1 = np.log(p1num / p1Denom)  # 属于侮辱性文档的概率
    return p0, p1, pInsult


# 分类函数
def classiyyNB(Inputdata, p0, p1, pInsult):
    # 因为取对数，因此连乘操作就变成了连续相加
    p0vec = np.sum(Inputdata * p0) + np.log(pInsult)
    p1vec = np.sum(Inputdata * p1) + np.log(1.0 - pInsult)
    if p0vec > p1vec:
        return 0
    else:
        return 1


def testingNB():
    dataset, label = loadDataSet()
    voast = createVocabList(dataset)
    listnewVocaset = []
    for listvocaset in dataset:
        listnewVocaset.append(setword(voast, listvocaset))
    p0, p1, pInsult = train(listnewVocaset, label)
    Inputdata = ['玩', '一', '玩']
    Inputdata = np.array(Inputdata)
    Inputdata = setword(voast, Inputdata)
    print("这句话对应的分类是：")
    print(classiyyNB(Inputdata, p0, p1, pInsult))


testingNB()
