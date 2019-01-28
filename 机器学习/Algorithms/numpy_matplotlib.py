import numpy as np
import matplotlib.pyplot as plt
import pandas as pd  # 基于两种数据类型series 和 dataframe

# Numpy
# a = np.array([0, 1, 2, 3, 4])
# b = np.array((0, 1, 2, 3, 4))
# c = np.arange(5)
# d = np.linspace(0, 2 * np.pi, 5)
# print(a)  # >>>[0 1 2 3 4]
# print(b)  # >>>[0 1 2 3 4]
# print(c)  # >>>[0 1 2 3 4]
# print(d)  # >>>[ 0.          1.57079633  3.14159265  4.71238898  6.28318531]
# print(a[3])  # >>>3
# # MD Array,
# a = np.array([[11, 12, 13, 14, 15],
#               [16, 17, 18, 19, 20],
#               [21, 22, 23, 24, 25],
#               [26, 27, 28, 29, 30],
#               [31, 32, 33, 34, 35]])
#
# print(a[2, 4])  # >>>25
# # MD slicing
# print(a[0, 1:4])  # >>>[12 13 14]
# print(a[1:4, 0])  # >>>[16 21 26]
# print(a[::2, ::2])  # >>>[[11 13 15]
# #     [21 23 25]
# #     [31 33 35]]
# print(a[:, 1])  # >>>[12 17 22 27 32]
#
# # Array properties
# a = np.array([[11, 12, 13, 14, 15],
#               [16, 17, 18, 19, 20],
#               [21, 22, 23, 24, 25],
#               [26, 27, 28, 29, 30],
#               [31, 32, 33, 34, 35]])
# # 存储形式
# print(type(a))  # >>><class 'numpy.ndarray'>
# # 数据类型
# print(a.dtype)  # >>>int64
# # 大小
# print(a.size)  # >>>25
# print(a.shape)  # >>>(5, 5)
# # 每一条所占的字节
# print(a.itemsize)  # >>>8
# # 维数
# print(a.ndim)  # >>>2
# # 所有元素占用的字节数
# print(a.nbytes)  # >>>200
#
# # dot, sum, min, max, cumsum
# a = np.arange(10)
#
# print(a.sum())  # >>>45
# print(a.min())  # >>>0
# print(a.max())  # >>>9
# print(a.cumsum())  # >>>[ 0  1  3  6 10 15 21 28 36 45]

# matplotlib
#折线图（plot）

# 简单的绘图
x = np.linspace(0, 2 * np.pi, 50)  # 生成一个包含 50 个元素的数组，这 50 个元素均匀的分布在 [0, 2pi] 的区间上
plt.plot(x, np.sin(x))  # 如果没有第一个参数 x，图形的 x 坐标默认为数组的索引
plt.show()  # 显示图形

# 自定义曲线的外观
# 颜色： 蓝色 - 'b' 绿色 - 'g' 红色 - 'r'
# 青色 - 'c' 品红 - 'm' 黄色 - 'y' 黑色 - 'k'
# （'b'代表蓝色，所以这里用黑色的最后一个字母） 白色 - 'w'
# 线： 直线 - '-' 虚线 - '--' 点线 - ':' 点划线 - '-.' 常用点标记 点 - '.'
# 像素 - ',' 圆 - 'o' 方形 - 's' 三角形 - '^'
x = np.linspace(0, 2 * np.pi, 50)
plt.plot(x, np.sin(x), 'r-o',
         x, np.cos(x), 'g--')
plt.show()

# 使用子图
#subplot() 函数，该函数的第一个参数代表子图的总行数，
# 第二个参数代表子图的总列数，第三个参数代表活跃区域。
#活跃区域代表当前子图所在绘图区域，绘图区域是按从左至右，从上至下的顺序编号。
# 例如在 4×4 的方格上，活跃区域 6 在方格上的坐标为 (2, 2)。
x = np.linspace(0, 2 * np.pi, 50)
plt.subplot(2, 1, 1) # （行，列，活跃区）
plt.plot(x, np.sin(x), 'r')
plt.subplot(2, 1, 2)
plt.plot(x, np.cos(x), 'g')
plt.show()

#折线图（scatter）

# 简单的散点图
x = np.linspace(0, 2 * np.pi, 50)
y = np.sin(x)
plt.scatter(x,y)
plt.show()

# 添加标题，坐标轴标记和图例
x = np.linspace(0, 2 * np.pi, 50)
plt.plot(x, np.sin(x), 'r-x', label='Sin(x)')
plt.plot(x, np.cos(x), 'g-^', label='Cos(x)')
plt.legend() # 展示图例
plt.xlabel('Rads') # 给 x 轴添加标签
plt.ylabel('Amplitude') # 给 y 轴添加标签
plt.title('Sin and Cos Waves') # 添加图形标题
plt.show()