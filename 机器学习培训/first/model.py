from builtins import range, len

import numpy as np
import matplotlib.pyplot as plt


class Linear:

    def __init__(self):
        self.alpha = 0.0
        self.bias = 0.0

    def predict(self, x):
        # f(x)
        return self.alpha * x + self.bias

    def draw(self, X, y):
        X = np.array(X)
        y = np.array(y)
        plt.scatter(X, y, color="R")  # 训练前的点图
        y_temp = self.predict(X)  # 带入函数后的函数值
        plt.plot(X, y_temp)  # 预测后的折线图
        plt.show()

    def train(self, X, label, learning_rate=1e-3,  # learning_rate为步长
              step=5000, batch_size=5):
        # 传入参数后都最好转换成nparray
        X = np.array(X)
        label = np.array(label)  # 样本
        for i in range(step):
            random_index = np.random.randint(low=0,
                                             high=len(X),
                                             size=batch_size)  # size是维度，在这里是生成的个数

            # 获取训练的数据
            X_train = X[random_index]  # 点的横轴
            y_train = label[random_index]  # 点的纵轴
            # 下面是精彩部分
            y_pre = self.predict(X_train)  # y_pre : (1,5)
            # loss = (y-y_pre)^2 ，方差
            loss = (y_train - y_pre) ** 2  # loss :(1,5)
            # 此时未知数为a和b，问题转换为求二元函数的最小值
            # 方法：梯度下降法
            print("loss:", np.sum(loss))
            # 方差对预测值求导
            dlossy_pre = -2 * (y_train - y_pre)  # loss :(1,5)
            df_alpha = X_train  # loss :(1,5)

            dloss_alpha = dlossy_pre * df_alpha * learning_rate  # loss :(1,5)

            self.alpha -= np.mean(dloss_alpha)  # 求平均值，梯度下降
            self.bias -= np.mean(dlossy_pre) * learning_rate
            print("a:", self.alpha)
            print("b", self.bias)


class multinomialModel:

    """
    在平方的基础上加入sin的模型
    """
    def __init__(self):
        self.alpha = 0.0
        self.beta = 0.0
        self.bias = 0.0
        self.gama = 1.0

        self.sin_a = 0.0
        self.sin_b = 0.0
        self.sin_bias = 0.0

        self.losses = []

    def predict(self, x):
        """
        y = a * x^2 + b * x + bias + gama * sin( sin_a * x^2 + sin_b * x + sin_bias)
        :param x:
        :return:
        """
        x = (x - np.mean(x)) / np.std(x)
        return self.alpha * x ** 2 + self.beta * x + self.bias + self.gama * np.sin(
            self.sin_a * x ** 2 + self.beta * x + self.sin_bias)

    def calculateLoss(self, y, y_pre):
        """
        计算误差
        :param y:
        :param y_pre:
        :return:
        """
        loss = np.mean((y - y_pre) ** 2)
        print("loss:%0.5f" % loss)
        self.losses.append(loss)

    def train(self, X, label, step, learning_rate, batch=1):
        """
        训练
        :param X:
        :param label:
        :param step:
        :param learning_rate:
        :param batch:
        :return:
        """
        X = np.array(X)
        X = (X - np.mean(X)) / np.std(X)
        label = np.array(label)

        for i in range(step):
            random_index = np.random.randint(low=0, high=len(X), size=batch)

            X_train = X[random_index]
            y = label[random_index]

            y_pre = self.predict(X_train)
            self.calculateLoss(y, y_pre)

            lossdf = -2 * (y - y_pre)

            dalpha = np.mean(lossdf * (X_train ** 2) * learning_rate)
            dbeta = np.mean(lossdf * X_train * learning_rate)
            dbias = np.mean(lossdf * learning_rate)

            dgama = np.mean(lossdf * np.sin(self.sin_a * X_train ** 2 + self.beta * X_train + self.sin_bias))
            dsin_a = np.mean(lossdf * self.gama * np.cos(
                self.sin_a * X_train ** 2 + self.beta * X_train + self.sin_bias) * X_train ** 2)
            dsin_b = np.mean(lossdf * self.gama * np.cos(
                self.sin_a * X_train ** 2 + self.beta * X_train + self.sin_bias) * X_train)
            dsin_bias = np.mean(lossdf * self.gama * np.cos(
                self.sin_a * X_train ** 2 + self.beta * X_train + self.sin_bias))

            self.alpha -= dalpha
            self.bias -= dbias
            self.beta -= dbeta
            self.gama -= dgama
            self.sin_a -= dsin_a
            self.sin_b -= dsin_b
            self.sin_bias -= dsin_bias

            # print(dalpha, dbeta, dbias, dgama, dsin_a, dsin_b, dsin_bias)

    def draw(self, X, y):
        plt.subplot(2, 1, 1)
        plt.scatter(X, y)
        x_temp = np.arange(start=-1, stop=len(y) + 5, step=0.1)
        y_pre = self.predict(x_temp)
        plt.plot(x_temp, y_pre)

        plt.subplot(2, 1, 2)
        plt.plot(range(len(self.losses)), self.losses)
        plt.show()


class StereMultinomial:
    """
    三次方的模型
    """
    def __init__(self):
        self.alpha = 0.0
        self.beta = 0.0
        self.gama = 0.0
        self.bias = 0.0

        self.losses = []

    def predict(self, x, isPre=False):
        """
        y = a * x^3 + b * x^2 + c * x + bias
        :param x:
        :return:
        """
        #标准化操作（标准化方法）
        if isPre:
            x = (x - np.mean(x)) / np.std(x)    #std是计算矩阵标准差
        return self.alpha * x ** 3 + self.beta * x ** 2 + self.gama * x + self.bias

    def calculateLoss(self, y, y_pre):
        """
        计算loss
        :param y:
        :param y_pre:
        :return:
        """
        loss = np.mean((y - y_pre) ** 2)
        self.losses.append(loss)
        print("loss:%0.4f" % loss)

    def train(self, X, y, step, batch_size, learning_rate):
        X = np.array(X)
        y = np.array(y)

        X = (X - np.mean(X)) / np.std(X)
        for i in range(step):
            random_index = np.random.randint(low=0, high=len(X), size=batch_size)
            X_train = X[random_index]
            y_train = y[random_index]

            y_pre = self.predict(X_train)
            if i % 100 == 0:
                self.calculateLoss(y_train, y_pre)
            if i % 20000 == 0:
                self.draw(X, y, True)

            dlossf = (-2) * (y_train - y_pre)

            dbias = np.mean(dlossf) * learning_rate
            dgama = np.mean(dlossf * X_train) * learning_rate
            dbeta = np.mean(dlossf * X_train ** 2) * learning_rate
            dalpha = np.mean(dlossf * X_train ** 3) * learning_rate

            self.alpha -= dalpha
            self.beta -= dbeta
            self.gama -= dgama
            self.bias -= dbias

    def draw(self, X, y, isTrain=False):
        plt.close()
        plt.subplot(2, 1, 1)
        plt.scatter(X, y)
        if isTrain:
            x_temp = X
            y_pre = self.predict(x_temp, isPre=True)
        else:
            x_temp = np.arange(start=-1, stop=len(y), step=0.1)
            y_pre = self.predict(x_temp, isPre=True)
        plt.plot(x_temp, y_pre)

        plt.subplot(2, 1, 2)
        plt.plot(range(len(self.losses)), self.losses)
        plt.show()


class LWRL:
    """
    局部加权回归
    """
    def predict(self, test_x, X, y, k):
        X = np.array(X)
        y = np.array(y)

        weights = np.eye(len(X))

        for i in range(len(X)):
            weights[i, i] = np.exp(-(test_x - X[i]) ** 2 / 2 * k ** 2)
        print(weights)

        # X:(1,size) , W:(size,size)
        xWx = np.dot(X, weights).dot(X.T)
        # theta = np.linalg.inv(xWx).dot(X).dot(weights).dot(y.T)
        theta = ((1.0 / xWx) * X).dot(weights).dot(y.T)
        return test_x * theta

    def draw(self, X, y, y_pred):
        plt.scatter(X, y)
        plt.plot(X, y_pred)
        plt.show()