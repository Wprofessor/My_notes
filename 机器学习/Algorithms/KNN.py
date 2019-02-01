import numpy as np


# KNN : k Nearest Neighbors
class k_nn:
    def knnPredict(self, newInput, dataset, labels, k):
        dataset = np.array(dataset)
        # 表示样本数量
        datasize = dataset.shape[0]
        # 求解欧式距离（类似于均方差）(x^2 + y^2)^0.5
        # tile属于numpy模块下边的函数
        # tile（A, reps）返回一个shape=reps的矩阵，矩阵的每个元素是A
        # 比如 A=[0,1,2] 那么，tile(A, 2)= [0, 1, 2, 0, 1, 2]
        # tile(A,(2,2)) = [[0, 1, 2, 0, 1, 2],
        #                  [0, 1, 2, 0, 1, 2]]
        # tile(A,(2,1,2)) = [[[0, 1, 2, 0, 1, 2]],
        #                    [[0, 1, 2, 0, 1, 2]]]
        # 上边那个结果的分开理解就是：
        # 最外层是2个元素，即最外边的[]中包含2个元素，类似于[C,D],而此处的C=D，因为是复制出来的
        # 然后C包含1个元素，即C=[E],同理D=[E]
        # 最后E包含2个元素，即E=[F,G],此处F=G，因为是复制出来的
        # F就是A了，基础元素
        # 综合起来就是(2,1,2)= [C, C] = [[E], [E]] = [[[F, F]], [[F, F]]] = [[[A, A]], [[A, A]]]
        # 这个地方就是为了把输入的测试样本扩展为和dataset的shape一样，然后就可以直接做矩阵减法了。
        # 比如，dataset有4个样本，就是4*2的矩阵，输入测试样本肯定是一个了，就是1*2，为了计算输入样本与训练样本的距离
        # 那么，需要对这个数据进行作差。这是一次比较，因为训练样本有n个，那么就要进行n次比较；
        # 为了方便计算，把输入样本复制n次，然后直接与训练样本作矩阵差运算，就可以一次性比较了n个样本。
        # 比如inX = [0,1],dataset就用函数返回的结果，那么
        # tile(inX, (4,1))= [[ 0.0, 1.0],
        #                    [ 0.0, 1.0],
        #                    [ 0.0, 1.0],
        #                    [ 0.0, 1.0]]
        # 作差之后
        # diffMat = [[-1.0,-0.1],
        #            [-1.0, 0.0],
        #            [ 0.0, 1.0],
        #            [ 0.0, 0.9]]
        diffMat = np.tile(newInput, (datasize, 1)) - dataset
        sqDisMat = diffMat ** 2
        # 对横轴进行求和
        sqDistance = np.sum(sqDisMat, axis=1)
        # 开根号
        distance = sqDistance ** 0.5
        # 对距离进行升序排序,返回的是数组下标
        sortDistance = distance.argsort()

        # 字典结构，存放对应的投票数
        classcount = {}

        # 投票过程
        for i in range(k):
            voteLabel = labels[sortDistance[i]]
            # 如果不存在这个类，则默认为0，每次都加1
            classcount[voteLabel] = classcount.get(voteLabel, 0) + 1

        # 返回一个降序的列表
        Realresult = sorted(classcount.items(), key=lambda item: item[1], reverse=True)
        return Realresult[0][0]


if __name__ == "__main__":
    model = k_nn()
    group = np.array([
        [1.0, 0.9],
        [1.0, 1.0],
        [0.1, 0.2],
        [0.0, 0.1]
    ])
    labels = ['A', 'A', 'B', 'B']
    newInput = [1.2, 1.0]
    print('the class of test sample is ' + model.knnPredict(newInput, group, labels, 3))
