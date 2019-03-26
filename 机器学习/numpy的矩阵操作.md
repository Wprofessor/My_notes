# numpy之python矩阵操作
## 1.不使用mat时矩阵的操作
##### 先导入numpy模块
```
import numpy as np
```
##### 矩阵乘法，不使用mat时，矩阵乘法要使用numpy里的dot方法
```
# np.dot() 矩阵乘法
a = np.array([[1, 2], [3, 4]])
b = np.array([[11, 12], [13, 14]])
print(np.dot(a, b))
# [[37 40]
#  [85 92]]

```
##### np.vdot(对应元素相乘求和
```
# 对应元素相乘求和
# np.vdot()
a = np.array([[1, 2], [3, 4]])
b = np.array([[11, 12], [13, 14]])
# vdot 将数组展开计算内积
print(np.vdot(a, b))
# 1*11 + 2*12 + 3*13 + 4*14 = 130
```
##### numpy.inner()返回一维向量内积
```
# numpy.inner()
print(np.inner(np.array([1, 2, 3]), np.array([0, 1, 0])))
# 等价于 1*0+2*1+3*0
```
##### numpy.linalg.det() 计算矩阵行列式
```
a = np.array([[1, 2], [3, 4]])
print(np.linalg.det(a))
# -2.0
```
###### numpy.linalg.inv()计算n阶矩阵的逆
```
x = np.array([[1, 2], [3, 4]])
y = np.linalg.inv(x)
print(x)
print(y)
# [[1 2]
#  [3 4]]
# [[-2.   1. ]
#  [ 1.5 -0.5]]
```

## 2.使用mat时矩阵的操作
##### 数组矩阵化
```
a1 = np.array([1, 2, 3])
a1 = np.mat(a1)  # 矩阵化
print(a1, a1.shape)
# [[1 2 3]] (1, 3)
```

##### 矩阵的创建
```
data1 = np.mat(np.zeros((3, 3)))  # 创建一个3*3的零矩阵
print(data1)
# [[ 0.  0.  0.]
#  [ 0.  0.  0.]
#  [ 0.  0.  0.]]

data2 = np.mat(np.ones((2, 4)))  # 创建一个2*4的1矩阵，默认为float类型，修改类型可以使用dtype
print(data2)
# [[ 1.  1.  1.  1.]
#  [ 1.  1.  1.  1.]]

data3 = np.mat(np.random.rand(2, 2))  # 随机生成2*2维度在0-1之间的数
print(data3)
# [[ 0.19641628  0.36173101]
#  [ 0.44323339  0.41273865]]

data4 = np.mat(np.random.randint(10, size=(3, 3)))  # 生成一个3*3的0-10之间的随机整数矩阵
print(data4)
# [[9 4 2]
#  [2 7 7]
#  [1 8 5]]


data5 = np.mat(np.random.randint(2, 8, size=(2, 5)))  # 产生一个2-8之间的随机整数矩阵
print(data5)
# [[3 3 6 5 5]
#  [6 7 7 4 3]]

data6 = np.mat(np.eye(2, 2, dtype=int))  # 产生一个2*2的对角矩阵(单位矩阵)
print(data6)
# [[1 0]
#  [0 1]]

a1 = [1, 2, 3]
a2 = np.mat(np.diag(a1))  # 生成一个对角线为1，2，3的对角矩阵
print(a2)
# [[1 0 0]
#  [0 2 0]
#  [0 0 3]]
```
##### 常见的矩阵运算
```
a1 = np.mat([1, 2])
a2 = np.mat([[1], [2]])
a3 = a1 * a2  # mat化后的矩阵相乘
print(a3)
# [[5]]
```

##### 矩阵点乘np.multiply()
```
a1 = np.mat([1, 2])
a2 = np.mat([2, 1])
a3 = np.multiply(a1, a2)  # 对应元素相乘
print(a3)
# [[2 2]]
```
###### 矩阵求逆与矩阵转置
```
a1 = np.mat(np.eye(2, 2) * 0.5)  # 创建一个0.5的对角矩阵
a2 = a1.I  # 矩阵求逆
print(a2)
# [[ 2.  0.]
#  [ 0.  2.]]

a1 = np.mat([[1, 1], [2, 3], [4, 2]])
a2 = a1.T  # 矩阵转置
print(a2)
# [[1 2 4]
#  [1 3 2]]
```
##### 计算矩阵对应行列的最大、最小值、和
```
a1 = np.mat([[1, 1], [2, 3], [4, 2]])
a2 = a1.sum(axis=0)  # 计算矩阵列的和
print(a2)
# [[7 6]]
a3 = a1.sum(axis=1)  # 计算矩阵行的和
print(a3)
# [[2]
#  [5]
#  [6]]
a4 = np.sum(a1[1, :])  # 计算第一行所有列的和，这里得到的是一个数值
print(a4)
# 5  第0行：1+1；第2行：2+3；第3行：4+2

# 计算最大最小值的索引
argmax(a, axis=None, out=None)
# a 表示array
# axis 表示指定的轴，默认是None，表示把array平铺，
# out 默认为None，如果指定，那么返回的结果会插入其中

print(np.argmax(a1, 0))	#计算所有列的最大值对应在该列中的索引
# [[2 1]]
print(np.argmax(a1[1, :]))  # 计算第二行中最大值对应在该行的索引
# 1
# 最小值同理
```
##### 矩阵的合并
```
a = np.mat(np.ones((2, 2)))
b = np.mat(np.eye(2))
c = np.vstack((a, b))  # 按列合并，增加行数
print(c)
# [[ 1.  1.]
#  [ 1.  1.]
#  [ 1.  0.]
#  [ 0.  1.]]
d = np.hstack((a, b))  # 按行合并，增加列数
print(d)
# [[ 1.  1.  1.  0.]
#  [ 1.  1.  0.  1.]]
```
### 不难发现mat化后的矩阵操作更加的简便
#### 使用mat和不使用的主要区别就是使用后 * 直接就是矩阵乘法，而不使用mat的话，* 代表对应元素相乘。。。通常如果涉及到矩阵操作都是经过mat化处理的。