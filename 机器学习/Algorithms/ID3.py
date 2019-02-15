from math import log


def creatDataset():
    dataset = [[1, 1, 'yes'],
               [1, 1, 'yes'],
               [1, 0, 'no'],
               [0, 1, 'no'],
               [0, 1, 'no']]
    labels = ['no surfacing', 'flippers']
    return dataset, labels


# 计算给定数据的经验熵
def calexShang(dataSet):
    num = len(dataSet)
    # 在字典里存储每个类别的数量
    labelcount = {}
    for val in dataSet:
        if val[-1] not in labelcount.keys():
            labelcount[val[-1]] = 1
        else:
            labelcount[val[-1]] += 1
    result = 0.0
    for key in labelcount:
        result -= ((float(labelcount[key])) / num) * log((float(labelcount[key])) / num, 2)
    return result


# 按照给定特征划分数据集
# axis:划分数据集的特征,value:特征可能的取值
def splitDataSet(dataSet, axis, value):
    reDataSet = []
    for val in dataSet:
        if val[axis] == value:
            x = val[:axis]
            # 得到一个删除此特征的列表
            x.extend(val[axis + 1:])
            reDataSet.append(x)
    # 列表中extend和append是有区别的
    # >>> a = [1,2,3]
    # >>> b = [4,5,6]
    # >>> a.append(b)
    # >>> a
    # [1,2,3,[4,5,6]]
    # >>>a.extend(b)
    # >>>a
    # [1,2,3,4,5,6]
    return reDataSet


# 根据信息增益选择最好的数据集划分方式
def chooseSplit(dataSet):
    num = len(dataset[0]) - 1
    ok = 0.0
    count = -1  # 标记最好的特征的索引
    # H(D)
    basicval = calexShang(dataset)
    for i in range(num):
        news = 0.0
        # 返回dataSet的列
        # [1, 1, 1, 0, 0]
        # [1, 1, 0, 1, 1]
        fealist = [example[i] for example in dataset]
        # 去重l
        vals = set(fealist)
        for value in vals:
            subDataSet = splitDataSet(dataset, i, value)
            prob = len(subDataSet) / float(len(dataset))
            news += prob * calexShang(subDataSet)
        result = basicval - news
        # 取信息增益大的特征为最优特征
        if result > ok:
            ok = result
            count = i
    return count


# 如果数据集已经处理了所有属性，但分类依然不唯一，则采取多数表决的方式确定分类(类似KNN的多数表决)
def ensureClassify(classList):
    classCount = {}
    for vote in classList:
        classCount[vote] = classCount.get(vote, 0) + 1
    Realresult = sorted(classCount.items(), key=lambda item: item[1], reverse=True)
    return Realresult[0][0]


# 创建决策树(递归)
def creatTree(dataSet, labels):
    classList = [example[-1] for example in dataset]
    # 如果类别相同，停止继续划分
    if classList.count(classList[0]) == len(classList):
        return classList[0]


dataset = [[1, 1, 'yes'],
           [1, 1, 'yes'],
           [1, 0, 'no'],
           [0, 1, 'no'],
           [0, 1, 'no']]
for i in range(len(dataset[0]) - 1):
    fealist = [example[i] for example in dataset]
    print(fealist)
