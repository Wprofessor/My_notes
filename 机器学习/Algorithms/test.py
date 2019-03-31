import numpy as np

import tensorflow as tf

x = np.random.random((200, 5))
w = np.random.random((5, 1))
print(w)
mu, sigma = 0, 0.1  # 均值与标准差
noise = np.random.normal(mu, sigma, (200, 1))
print(noise)

a = tf.constant([1.0, 2.0], name="a")
b = tf.constant([2.0, 3.0], name="b")
print(a + b)
 