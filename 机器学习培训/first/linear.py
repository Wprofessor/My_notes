import numpy as np
from model import Linear
from model import Multinomial
# 数据可视化
import matplotlib.pyplot as plt


def load_data():
    path = "./data/linear_data.txt"
    file = open(path)
    str = file.read()
    raw_data = str.split("，")
    # print(raw_data)
    int_data = np.array(raw_data, dtype=int)
    # print(int_data)
    return int_data


def draw(X):
    plt.scatter(range(len(X)), X)
    # plt.plot(range(len(X)), X, color="R")
    plt.show()


def linear(X, y):
    model = Linear()
    model.train(X, y, 1e-4)
    model.draw(X, y)


def multinomial(X, y):
    model = Multinomial()
    model.train(X, y, 1e-5, step=10000)
    model.draw(X, y)


if __name__ == "__main__":
    int_data = load_data()
    print(int_data)
    draw(int_data)
    print(int_data)
    linear(range(len(int_data)), int_data)
        # x = range(len(int_data))
    # multinomial(x,int_data)
