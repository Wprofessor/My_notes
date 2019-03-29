import numpy as np

x = np.random.random((200, 5))
w = np.random.random((5, 1))
print(w)
mu, sigma = 0, 0.1  # 均值与标准差
noise = np.random.normal(mu, sigma, (200, 1))
print(noise)
