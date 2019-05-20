import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

INPUT_NODE = 784  # 输入层节点数，相当于图片像素
OUTPUT_NODE = 10  # 输出层节点数，相当于类别数目

# 配置神经网络参数
LAYERL_NODE = 500  # 隐含层节点数

BATCH_SIZE = 100  # 每个训练batch的训练数据个数，数字越小，越接近随机梯度下降，否则越接近梯度下降

LEARNING_RATE_BASE = 0.8  # 基础的学习率
LEARNING_RATE_DECAY = 0.99  # 学习率的衰减率
REGULARIZATION_RATE = 0.0001  # 正则化项系数
TRAINING_STEPS = 30000  # 训练轮数
MOVING_AVERAGE_DACAY = 0.99  # 滑动平均衰减率


# 计算神经网络的前向传播结果的辅助函数
# 这里使用RELU激活函数
def inference(input_tensor, avg_class, weights1, biases1, weights2, biases2):
    # 当没有提供滑动平均类时
    if avg_class == None:
        # 计算隐含层的前向传播结果
        layer1 = tf.nn.relu(tf.matmul(input_tensor, weights1) + biases1)

        # 计算输出层的前向传播结果，计算损失函数时一并计算Softmax函数（将结果转化为概分布）
        # 所以不用加入激活函数，不加入softmax不回影响那个结果
        return tf.matmul(layer1, weights2) + biases2
    else:
        # 首先结算变量的滑动平均值在计算前向传播结果
        layer1 = tf.nn.relu(tf.matmul(input_tensor, avg_class.average(weights1)) + avg_class.average(biases1))
        return tf.matmul(layer1, avg_class.average(weights2)) + avg_class.average(biases2)


# 训练模型的过程
def train(mnist):
    x = tf.placeholder(tf.float32, [None, INPUT_NODE], name='x-input')
    y_ = tf.placeholder(tf.float32, [None, OUTPUT_NODE], name='y-input')

    # 生成隐藏层的参数
    weights1 = tf.Variable(
        tf.truncated_normal([INPUT_NODE, LAYERL_NODE], stddev=0.1))
    biases1 = tf.Variable(tf.constant(0.1, shape=[LAYERL_NODE]))
    # 生成输出层的参数
    weights2 = tf.Variable(
        tf.truncated_normal([LAYERL_NODE, OUTPUT_NODE], stddev=0.1))
    biases2 = tf.Variable(tf.constant(0.1, shape=[OUTPUT_NODE]))
    # 计算前向传播结果
    y = inference(x, None, weights1, biases1, weights2, biases2)

    # 定义存储训练轮数的变量，指定为不可训练的变量
    global_step = tf.Variable(0, trainable=False)

    # 初始化滑动平均类
    variable_averages = tf.train.ExponentialMovingAverage(MOVING_AVERAGE_DACAY, global_step)

    # 在所有神经网络参数上使用滑动平均(所有可训练的变量)
    variable_averages_op = variable_averages.apply(tf.trainable_variables())

    # 计算使用了滑动平均之后的前向传播结果
    average_y = inference(x, variable_averages, weights1, biases1, weights2, biases2)

    # 计算交叉熵的损失函数
    # argmax(y_,1)返回的是最大值的下标
    cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=y, labels=tf.argmax(y_, 1))
    # 计算在当前batch中所有样例的交叉熵平均值
    cross_entropy_mean = tf.reduce_mean(cross_entropy)

    # 计算L2正则化损失函数
    regularize = tf.contrib.layers.l2_regularizer(REGULARIZATION_RATE)
    # 计算模型的正则化损失
    regularization = regularize(weights1) + regularize(weights2)
    # 总损失等于交叉熵损失和正则化损失的和
    loss = cross_entropy_mean + regularization
    # 设置指数衰减的学习率
    learning_rate = tf.train.exponential_decay(LEARNING_RATE_BASE, global_step, mnist.train.num_examples / BATCH_SIZE,
                                               LEARNING_RATE_DECAY)
    # 优化损失函数
    train_step = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss, global_step=global_step)

    # 每过一遍数据都要更新每一个参数的滑动平均值
    train_op = tf.group(train_step, variable_averages_op)
    # 检验使用了滑动平均模型的神经网络前向传播结果是否正确
    correct_prediction = tf.equal(tf.argmax(average_y, 1), tf.argmax(y_, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    # 初始化会话并开始训练过程
    with tf.Session() as sess:
        tf.global_variables_initializer().run()

        # 准备验证数据
        validate_feed = {x: mnist.validation.images,
                         y_: mnist.validation.labels}

        # 准备测试数据
        test_feed = {x: mnist.test.images,
                     y_: mnist.test.labels}

        # 迭代的训练神经网络
        for i in range(TRAINING_STEPS):
            if i % 1000 == 0:
                # 计算滑动平均模型在验证数据集上的结果
                validate_acc = sess.run(accuracy, feed_dict=validate_feed)
                print(i, "次训练之后，平均正确率为:", validate_acc)

            # 产生这一轮使用的batch的训练数据，并运行训练过程
            xs, ys = mnist.train.next_batch(BATCH_SIZE)
            sess.run(train_op, feed_dict={x: xs, y_: ys})

        # 训练结束后，在测试数据上检验伸进网络最终正确率
        test_acc = sess.run(accuracy, feed_dict=test_feed)
        print('最终检验结果', test_acc)


def main(argv=None):
    mnist = input_data.read_data_sets("C:\\Users\\王教授\\Desktop\\MNIST_Data", one_hot=True)
    train(mnist)


if __name__ == '__main__':
    tf.app.run()
