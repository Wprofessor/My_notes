from numpy.random import RandomState
import tensorflow as tf

rdm = RandomState(1)
dataste_size = 128
X = rdm.rand(dataste_size, 2)
Y = [[int(x1 + x2 < 1)] for [x1, x2] in X]


print(Y)