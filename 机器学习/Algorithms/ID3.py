from math import log
import pickle


def creatDataset():
    # 数据集
    dataSet = [[0, 0, 0, 0, 'no'],
               [0, 0, 0, 1, 'no'],
               [0, 1, 0, 1, 'yes'],
               [0, 1, 1, 0, 'yes'],
               [0, 0, 0, 0, 'no'],
               [1, 0, 0, 0, 'no'],
               [1, 0, 0, 1, 'no'],
               [1, 1, 1, 1, 'yes'],
               [1, 0, 1, 2, 'yes'],
               [1, 0, 1, 2, 'yes'],
               [2, 0, 1, 2, 'yes'],
               [2, 0, 1, 1, 'yes'],
               [2, 1, 0, 1, 'yes'],
               [2, 1, 0, 2, 'yes'],
               [2, 0, 0, 0, 'no']]
    # 分类属性
    labels = ['年龄', '有工作', '有自己的房子', '信贷情况']
    return dataSet, labels


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
def chooseSplit(dataset):
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
    classList = [example[-1] for example in dataSet]
    # 如果类别相同，停止继续划分
    if classList.count(classList[0]) == len(classList):
        return classList[0]
    # 如果数据集已经处理了所有属性，但分类依然不唯一，则采取多数表决的方式确定分类
    if len(dataSet[0]) == 1:
        return ensureClassify(classList)
    bestFest = chooseSplit(dataSet)  # 得到最优特征的索引
    bestFestLabel = labels[bestFest]
    # 用字典的结构建树
    myTree = {bestFestLabel: {}}
    del (labels[bestFest])  # 删除当前最优特征
    # 注意：del方法删除的是变量，而不是数据
    # a=1       对象 1 被 变量a引用，对象1的引用计数器为1
    # b=a        对象1 被变量b引用，对象1的引用计数器加1
    # c=a       1对象1 被变量c引用，对象1的引用计数器加1
    # del a     删除变量a，解除a对1的引用
    # del b     删除变量b，解除b对1的引用
    # print(c)  最终变量c仍然引用1
    # li=[1,2,3,4,5]  列表本身不包含数据1,2,3,4,5，而是包含变量：li[0] li[1] li[2] li[3] li[4]
    # first=li[0]     拷贝列表，也不会有数据对象的复制，而是创建新的变量引用
    # del li[0]
    # print(li)      输出[2, 3, 4, 5]
    # print(first)   输出 1
    featValue = [example[bestFest] for example in dataSet]  # 得到最优特征的所有属性值
    uniqueVals = set(featValue)  # 去重
    for value in uniqueVals:
        subLabels = labels[:]  # 复制特征种类
        # 递归建树
        # 使用嵌套字典构造树结构
        myTree[bestFestLabel][value] = creatTree(splitDataSet(dataSet, bestFest, value), subLabels)
    return myTree
    # 构造的字典大概是这样
    # {'no surfacing': {0: 'no', 1: {'flippers': {0: 'no', 1: 'yes'}}}}


# 使用决策树进行分类(递归)
# testFeat：样例特征
def classify(inputTree, Labels, testFeat):
    firstStr = list(inputTree.keys())[0]  # 表示根节点
    secondDict = inputTree[firstStr]  # 表示根节点的儿子
    featIndex = Labels.index(firstStr)  # 标签的索引
    for key in secondDict.keys():
        if testFeat[featIndex] == key:
            # 如果不是叶子节点，递归继续遍历
            if type(secondDict[key]) == dict:
                classLable = classify(secondDict[key], Labels, testFeat)
            else:
                classLable = secondDict[key]
    return classLable


# 将决策树保存在硬盘上
def storeTree(inputTree, filename):
    fw = open(filename, 'wb+')
    pickle.dump(inputTree, fw)
    fw.close()


# 读取保存的决策树的内容
def grabTree(filename):
    fr = open(filename, 'rb')
    return pickle.load(fr)


dataSet, labels = creatDataset()
tree = creatTree(dataSet, labels)
print(tree)
# 将对象序列化为string形式，而不是存入文件中。
# storeTree(tree, 'classifyTree.txt')
print(grabTree('classifyTree.txt'))
dataSet, labels = creatDataset()
print(classify(tree, labels, [0, 1, 0, 0]))
