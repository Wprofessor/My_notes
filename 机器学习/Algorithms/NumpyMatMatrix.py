import numpy as np

#
# a1 = np.array([1, 2, 3])
# a1 = np.mat(a1)  # 矩阵化
# print(a1, a1.shape)
# # [[1 2 3]] (1, 3)
#
# # 矩阵的创建
# data1 = np.mat(np.zeros((3, 3)))  # 创建一个3*3的零矩阵
# print(data1)
# # [[ 0.  0.  0.]
# #  [ 0.  0.  0.]
# #  [ 0.  0.  0.]]
#
# data2 = np.mat(np.ones((2, 4)))  # 创建一个2*4的1矩阵，默认为float类型，修改类型可以使用dtype
# print(data2)
# # [[ 1.  1.  1.  1.]
# #  [ 1.  1.  1.  1.]]
#
# data3 = np.mat(np.random.rand(2, 2))  # 随机生成2*2维度在0-1之间的数
# print(data3)
# # [[ 0.19641628  0.36173101]
# #  [ 0.44323339  0.41273865]]
#
# data4 = np.mat(np.random.randint(10, size=(3, 3)))  # 生成一个3*3的0-10之间的随机整数矩阵
# print(data4)
# # [[9 4 2]
# #  [2 7 7]
# #  [1 8 5]]
#
#
# data5 = np.mat(np.random.randint(2, 8, size=(2, 5)))  # 产生一个2-8之间的随机整数矩阵
# print(data5)
# # [[3 3 6 5 5]
# #  [6 7 7 4 3]]
#
# data6 = np.mat(np.eye(2, 2, dtype=int))  # 产生一个2*2的对角矩阵(单位矩阵)
# print(data6)
# # [[1 0]
# #  [0 1]]

# a1 = [1, 2, 3]
# a2 = np.mat(np.diag(a1))  # 生成一个对角线为1，2，3的对角矩阵
# print(a2)
# # [[1 0 0]
# #  [0 2 0]
# #  [0 0 3]]

# # 常见的矩阵运算
# a1 = np.mat([1, 2])
# a2 = np.mat([[1], [2]])
# a3 = a1 * a2  # mat化后的矩阵相乘
# print(a3)
# # [[5]]

# # 矩阵点乘
# a1 = np.mat([1, 2])
# a2 = np.mat([2, 1])
# a3 = np.multiply(a1, a2)    # 对应元素相乘
# print(a3)
# # [[2 2]]

# 