# bp神经网络进行分类

import math
import random

random.seed(0)


# 生成区间[a, b)内的随机数
def rand(a, b):
    return (b - a) * random.random() + a


# 生成大小 I*J 的矩阵，默认零矩阵 (当然，亦可用 NumPy 提速)
def makeMatrix(I, J, fill=0.0):
    m = []
    for i in range(I):
        m.append([fill] * J)
    return m


# 函数 sigmoid，这里采用 tanh，因为看起来要比标准的 1/(1+e^-x) 漂亮些
def sigmoid(x):
    return math.tanh(x)


# 函数 sigmoid 的派生函数, 为了得到输出 (即：y)
def dsigmoid(y):
    return 1.0 - y ** 2


class NN:
    ' 三层反向传播神经网络 '

    def __init__(self, ni, nh, no):
        # 输入层、隐藏层、输出层的节点（数）
        self.ni = ni + 1  # 增加一个偏差节点
        self.nh = nh
        self.no = no

        # 激活神经网络的所有节点（向量）
        self.ai = [1.0] * self.ni
        self.ah = [1.0] * self.nh
        self.ao = [1.0] * self.no

        # 建立权重（矩阵）
        self.wi = makeMatrix(self.ni, self.nh)
        self.wo = makeMatrix(self.nh, self.no)
        # 设为随机值
        for i in range(self.ni):
            for j in range(self.nh):
                self.wi[i][j] = rand(-0.2, 0.2)
        for j in range(self.nh):
            for k in range(self.no):
                self.wo[j][k] = rand(-2.0, 2.0)

        # 最后建立动量因子（矩阵）
        # 动量因子：当前梯度方向与前一步的梯度方向一样，那么就增加这一步的权值更新，要是不一样就减少更新。
        self.ci = makeMatrix(self.ni, self.nh)
        self.co = makeMatrix(self.nh, self.no)

    def update(self, inputs):
        if len(inputs) != self.ni - 1:
            raise ValueError('与输入层节点数不符！')

        # 激活输入层
        for i in range(self.ni - 1):
            # self.ai[i] = sigmoid(inputs[i])
            self.ai[i] = inputs[i]

        # 激活隐藏层
        for j in range(self.nh):
            sum = 0.0
            for i in range(self.ni):
                sum = sum + self.ai[i] * self.wi[i][j]
            self.ah[j] = sigmoid(sum)

        # 激活输出层
        for k in range(self.no):
            sum = 0.0
            for j in range(self.nh):
                sum = sum + self.ah[j] * self.wo[j][k]
            # self.ao[k] = sigmoid(sum)    # 修改的
            self.ao[k] = sum
        return self.ao[:]

    def backPropagate(self, case, targets, N, M):
        ''' 反向传播 '''
        if len(targets) != self.no:
            raise ValueError('与输出层节点数不符！')

        self.update(case)
        # 计算输出层的误差
        output_deltas = [0.0] * self.no
        for k in range(self.no):
            error = targets[k] - self.ao[k]
            # output_deltas[k] = dsigmoid(self.ao[k]) * error
            output_deltas[k] = error        # 修改的

        # 计算隐藏层的误差
        hidden_deltas = [0.0] * self.nh
        for j in range(self.nh):
            error = 0.0
            for k in range(self.no):
                error = error + output_deltas[k] * self.wo[j][k]
            hidden_deltas[j] = dsigmoid(self.ah[j]) * error

        # 更新输出层权重
        for j in range(self.nh):
            for k in range(self.no):
                change = output_deltas[k] * self.ah[j]
                self.wo[j][k] = self.wo[j][k] + N * change + M * self.co[j][k]
                self.co[j][k] = change
                # print(N*change, M*self.co[j][k])

        # 更新输入层权重
        for i in range(self.ni):
            for j in range(self.nh):
                change = hidden_deltas[j] * self.ai[i]
                self.wi[i][j] = self.wi[i][j] + N * change + M * self.ci[i][j]
                self.ci[i][j] = change

        # 计算误差
        error = 0.0
        for k in range(len(targets)):
            error = error + 0.5 * (targets[k] - self.ao[k]) ** 2
        return error

    def test(self, patterns):
        for p in patterns:
            print(p[0], '->', self.update(p[0]))

    def weights(self):
        print('输入层权重:')
        for i in range(self.ni):
            print(self.wi[i])
        print()
        print('输出层权重:')
        for j in range(self.nh):
            print(self.wo[j])

    def train(self, patterns, iterations=1000, N=0.03, M=0.1):
        # N: 学习速率(learning rate)
        # M: 动量因子(momentum factor)
        for i in range(iterations):
            error = 0.0
            for p in patterns:
                inputs = p[0]
                targets = p[1]
                error = error + self.backPropagate(inputs, targets, N, M)
            if i % 100 == 0:
                print('误差 %-.5f' % error)


def demo():
    # 一个演示：教神经网络学习逻辑异或（XOR）------------可以换成你自己的数据试试
    # pat = [
    #     [[0, 0], [0]],
    #     [[0, 1], [1]],
    #     [[1, 0], [1]],
    #     [[1, 1], [0]]
    # ]

    pat = [
        [[1, 2], [3]],
        [[4, 4.5], [9]],
        [[1, 0], [1]],
        [[1, 1], [2]]
    ]
    # 创建一个神经网络：输入层有两个节点、隐藏层有两个节点、输出层有一个节点
    n = NN(2, 7, 1)
    # 用一些模式训练它
    n.train(pat)
    # 测试训练的成果（不要吃惊哦）
    n.test(pat)
    # 看看训练好的权重（当然可以考虑把训练好的权重持久化）
    # n.weights()


if __name__ == '__main__':
    demo()

# # 修改思路
# # 最后一层不激活，直接输出。或者说把激活函数看作f(x)=x
# # bp神经网络进行回归预测
#
# import math
# import random
#
# random.seed(0)
#
#
# def rand(a, b):
#     return (b - a) * random.random() + a
#
#
# def make_matrix(m, n, fill=0.0):
#     mat = []
#     for i in range(m):
#         mat.append([fill] * n)
#     return mat
#
#
# def sigmoid(x):
#     return 1.0 / (1.0 + math.exp(-x))
#
#
# def sigmoid_derivative(x):
#     return x * (1 - x)
#
#
# class BPNeuralNetwork:
#     def __init__(self):
#         self.input_n = 0
#         self.hidden_n = 0
#         self.output_n = 0
#         self.input_cells = []
#         self.hidden_cells = []
#         self.output_cells = []
#         self.input_weights = []
#         self.output_weights = []
#         self.input_correction = []
#         self.output_correction = []
#
#     def setup(self, ni, nh, no):
#         self.input_n = ni + 1
#         self.hidden_n = nh
#         self.output_n = no
#         # init cells
#         self.input_cells = [1.0] * self.input_n
#         self.hidden_cells = [1.0] * self.hidden_n
#         self.output_cells = [1.0] * self.output_n
#         # init weights
#         self.input_weights = make_matrix(self.input_n, self.hidden_n)
#         self.output_weights = make_matrix(self.hidden_n, self.output_n)
#         # random activate
#         for i in range(self.input_n):
#             for h in range(self.hidden_n):
#                 self.input_weights[i][h] = rand(-0.2, 0.2)
#         for h in range(self.hidden_n):
#             for o in range(self.output_n):
#                 self.output_weights[h][o] = rand(-2.0, 2.0)
#         # init correction matrix
#         self.input_correction = make_matrix(self.input_n, self.hidden_n)
#         self.output_correction = make_matrix(self.hidden_n, self.output_n)
#
#     def predict(self, inputs):
#         # activate input layer
#         for i in range(self.input_n - 1):
#             self.input_cells[i] = inputs[i]  # 输入层输出值
#         # activate hidden layer
#         for j in range(self.hidden_n):
#             total = 0.0
#             for i in range(self.input_n):
#                 total += self.input_cells[i] * self.input_weights[i][j]  # 隐藏层输入值
#             self.hidden_cells[j] = sigmoid(total)  # 隐藏层的输出值
#         # activate output layer
#         for k in range(self.output_n):
#             total = 0.0
#             for j in range(self.hidden_n):
#                 total += self.hidden_cells[j] * self.output_weights[j][k]
#                 # -----------------------------------------------
#             # self.output_cells[k] = sigmoid(total)
#             self.output_cells[k] = total  # 输出层的激励函数是f(x)=x
#         # -----------------------------------------------
#         return self.output_cells[:]
#
#     def back_propagate(self, case, label, learn, correct):  # x,y,修改最大迭代次数， 学习率λ， 矫正率μ三个参数.
#         # feed forward
#         self.predict(case)
#         # get output layer error
#         output_deltas = [0.0] * self.output_n
#         for o in range(self.output_n):
#             error = label[o] - self.output_cells[o]
#             # -----------------------------------------------
#             # output_deltas[o] = sigmoid_derivative(self.output_cells[o]) * error
#             output_deltas[o] = error
#         # -----------------------------------------------
#         # get hidden layer error
#         hidden_deltas = [0.0] * self.hidden_n
#         for h in range(self.hidden_n):
#             error = 0.0
#             for o in range(self.output_n):
#                 error += output_deltas[o] * self.output_weights[h][o]
#             hidden_deltas[h] = sigmoid_derivative(self.hidden_cells[h]) * error
#
#         # update output weights
#         for h in range(self.hidden_n):
#             for o in range(self.output_n):
#                 change = output_deltas[o] * self.hidden_cells[h]
#                 self.output_weights[h][o] += learn * change + correct * self.output_correction[h][o]  # ？？？？？？？？？？
#                 self.output_correction[h][o] = change
#
#         # update input weights
#         for i in range(self.input_n):
#             for h in range(self.hidden_n):
#                 change = hidden_deltas[h] * self.input_cells[i]
#                 self.input_weights[i][h] += learn * change + correct * self.input_correction[i][h]
#                 self.input_correction[i][h] = change
#         # get global error
#         error = 0.0
#         for o in range(len(label)):
#             error += 0.5 * (label[o] - self.output_cells[o]) ** 2
#         return error
#
#     def train(self, cases, labels, limit=10000, learn=0.05, correct=0.1):
#         for j in range(limit):
#             error = 0.0
#             for i in range(len(cases)):
#                 label = labels[i]
#                 case = cases[i]
#                 error += self.back_propagate(case, label, learn, correct)
#
#     def test(self):
#         cases = [
#             [1, 2],
#             [4, 4.5],
#             [1, 0],
#             [1, 1],
#         ]
#         labels = [[3], [9], [1], [2]]
#         self.setup(2, 5, 1)
#         self.train(cases, labels, 10000, 0.05, 0.1)
#         for case in cases:
#             print(self.predict(case))
#
#
# if __name__ == '__main__':
#     nn = BPNeuralNetwork()
#     nn.test()
