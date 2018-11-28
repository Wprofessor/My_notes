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
        plt.scatter(X, y, color="R")    #训练前的点图
        y_temp = self.predict(X)         #带入函数后的函数值
        plt.plot(X, y_temp)              #预测后的折线图
        plt.show()

    def train(self, X, label, learning_rate=1e-3,
              step=5000, batch_size=5):
        # 传入参数后都最好转换成nparray
        X = np.array(X)
        label = np.array(label)    #样本
        for i in range(step):
            random_index = np.random.randint(low=0,
                                             high=len(X),
                                             size=batch_size)       #size是维度，在这里是生成的个数

            # 获取训练的数据
            X_train = X[random_index]  # 点的横轴
            y_train = label[random_index]  # 点的纵轴
            # 下面是精彩部分
            y_pre = self.predict(X_train)  # y_pre : (1,5)
            # loss = (y-y_pre)^2 ，方差
            loss = (y_train - y_pre) ** 2  # loss :(1,5)
            print("loss:", np.sum(loss))
            # 方差对预测值求导
            dlossy_pre = -2 * (y_train - y_pre)  # loss :(1,5)
            df_alpha = X_train  # loss :(1,5)

            dloss_alpha = dlossy_pre * df_alpha * learning_rate  # loss :(1,5)

            self.alpha -= np.mean(dloss_alpha)        #求平均值
            self.bias -= np.mean(dlossy_pre) * learning_rate


class Multinomial:

    def __init__(self):
        self.alpha = 0.0
        self.bias = 0.0
        self.beta = 0.0
        self.gama = 0.0

    def predict(self, X):
        X = np.array(X)
        return self.alpha * X ** 3 + \
               self.beta * X ** 2 + \
               self.gama * X + \
               self.bias

    def draw(self, X, y):
        X = np.array(X)
        y = np.array(y)
        plt.scatter(X, y, color="R")
        y_temp = self.predict(X)
        plt.plot(X, y_temp)
        plt.show()

    def train(self, X, label, learning_rate=1e-3,
              step=5000, batch_size=5):
        # 传入参数后都最好转换成nparray
        X = np.array(X)
        label = np.array(label)
        for i in range(step):
            random_index = np.random.randint(low=0,
                                             high=len(X),
                                             size=batch_size)
            # 获取训练的数据
            X_train = X[random_index]  # 点的横轴
            y_train = label[random_index]  # 点的纵轴
            # 下面是精彩部分
            y_pre = self.predict(X_train)  # y_pre : (1,5)
            # loss = (y-y_pre)^2 ，方差
            loss = (y_train - y_pre) ** 2  # loss :(1,5)
            print("loss:", np.sum(loss))
            # 方差对预测值求导
            dlossy_pre = -2 * (y_train - y_pre)  # loss :(1,5)

            # y = alpha * x^3 + beta * x^2 + gama * x + bias
            dalpha = np.mean(dlossy_pre * X_train ** 3) * learning_rate
            dbeta = np.mean(dlossy_pre * X_train ** 2) * learning_rate
            dgama = np.mean(dlossy_pre * X_train) * learning_rate
            dbias = np.mean(dlossy_pre) * learning_rate

            self.alpha -= dalpha
            self.beta -= dbeta
            self.gama -= dgama
            self.bias -= dbias