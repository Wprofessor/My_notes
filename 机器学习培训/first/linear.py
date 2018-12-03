import numpy as np
from model import Linear
from model import multinomialModel
from model import LWRL
from model import StereMultinomial
# 数据可视化
import matplotlib.pyplot as plt
def load_data():
    path = "./data/temperature.txt"
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


def MultinomialModel(X, y):
    model = multinomialModel()
    model.train(X, y,5000,1e-7,5)
    model.draw(X, y)

def lwrl(X, y):
    model = LWRL()
    preds = []
    for i in range(len(X)):
        pred = model.predict(X[i], X, y, k=1)
        preds.append(pred)
    model.draw(X, y, preds)

def stereMultinomialModel(X, y):
    model = StereMultinomial()
    model.train(X, y, 500000, 20, 1e-5)
    model.draw(X, y)
if __name__ == "__main__":
    int_data = load_data()
    print(int_data)
    draw(int_data)
    print(int_data)
    # linear(range(len(int_data)), int_data)
    # x = range(len(int_data))
    x = np.arange(start=1, stop=len(int_data) + 1, step=1)
    # MultinomialModel(x, int_data)
    # lwrl(x,int_data)
    stereMultinomialModel(x,int_data)