import tensorflow as tf

# 生成模拟数据集
from numpy.random import RandomState

# 定义训练数据batch的大小
batch_size = 8

# 定义神经网络参数
w1 = tf.Variable(tf.random_normal((2, 3), stddev=1, seed=1))
w2 = tf.Variable(tf.random_normal((3, 1), stddev=1, seed=1))

# 在shape中使用none方便使用不同的batch大小。
# 训练时需要把数据分成比较小的batch
# 测试时，可以一次性使用全部数据
x = tf.placeholder(tf.float32, shape=(None, 2), name='x-input')
y_ = tf.placeholder(tf.float32, shape=(None, 1), name='y-input')

# 定义神经网络的传播过程
a = tf.matmul(x, w1)
y = tf.matmul(a, w2)

# 定义损失函数和反向传播算法。
y = tf.sigmoid(y)
cross_entropy = -tf.reduce_mean(
    y_ * tf.log(tf.clip_by_value(y, 1e-10, 1.0))
    + (1 - y_) * tf.log(tf.clip_by_value(1 - y, 1e-10, 1.0)))
train_step = tf.train.AdamOptimizer(0.001).minimize(cross_entropy)

# 随机生成一个模拟数据集
rdm = RandomState(1)
dataste_size = 128
X = rdm.rand(dataste_size, 2)

# x1+x2 < 1 表示正样本，否则为负样本
Y = [[int(x1 + x2 < 1)]for [x1, x2] in X]

# 创建一个会话运行Tensorflow程序
with tf.Session() as sess:
    init_op = tf.global_variables_initializer()
    # 初始化变量
    sess.run(init_op)

    # 设定训练的轮数
    STEPS = 5000
    for i in range(STEPS):
        # 每次选取batch_size个样本进行训练
        start = (i * batch_size) % dataste_size
        end = min(start + batch_size, dataste_size)

        # 通过选取的样本训练神经网络更新参数
        sess.run(train_step, feed_dict={x: X[start:end], y_: Y[start: end]})
        if i % 1000 == 0:
            # 输出所有数据上的交叉熵
            total_cross_entropy = sess.run(cross_entropy, feed_dict={x: X, y_: Y})
            print('训练第', i, '次的交叉熵是：', total_cross_entropy)
    print(sess.run(w1))
    print(sess.run(w2))