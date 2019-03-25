# numpy之python矩阵(array)操作
import numpy as np

# np.dot() 矩阵乘法
a = np.array([[1, 2], [3, 4]])
b = np.array([[11, 12], [13, 14]])
print(np.dot(a, b))
# [[37 40]
#  [85 92]]

# np.vdot() 对应元素相乘求和
a = np.array([[1, 2], [3, 4]])
b = np.array([[11, 12], [13, 14]])
# vdot 将数组展开计算内积
print(np.vdot(a, b))
# 1*11 + 2*12 + 3*13 + 4*14 = 130

# numpy.inner() fanhui一维向量内积
print(np.inner(np.array([1, 2, 3]), np.array([0, 1, 0])))
# 等价于 1*0+2*1+3*0

# numpy.linalg.det() 计算矩阵行列式
a = np.array([[1, 2], [3, 4]])
print(np.linalg.det(a))
# -2.0

# numpy.linalg.inv() 计算n阶矩阵的逆
x = np.array([[1, 2], [3, 4]])
y = np.linalg.inv(x)
print(x)
print(y)
# [[1 2]
#  [3 4]]
# [[-2.   1. ]
#  [ 1.5 -0.5]]