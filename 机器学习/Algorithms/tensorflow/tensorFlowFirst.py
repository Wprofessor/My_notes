from tensorflow.examples.tutorials.mnist import input_data
import tensorflow as tf

# 1 准备place holder用来传入数据使用

# x, y的shape都使用是None, 这个值就是一个可变的batch_size
X = tf.placeholder(tf.float32, shape=[None, 784], name='X_placeholder')
Y = tf.placeholder(tf.float32, shape=[None, 10], name='Y_placeholder')
mnist_data = input_data.read_data_sets("C:\\Users\\王教授\\Desktop\\MNIST_Data", one_hot=True)
# 2 设置变量，这里使用2个隐层+一个输出层来设置变量，所以就是3个W和3个bias
n_hidden_1 = 256  # 第1个隐层
n_hidden_2 = 256  # 第2个隐层
n_input = 784  # 输入
n_classes = 10  # 分类

weights = {
    'h1': tf.Variable(tf.random_normal([n_input, n_hidden_1]), name='W1'),
    'h2': tf.Variable(tf.random_normal([n_hidden_1, n_hidden_2]), name='W2'),
    'out': tf.Variable(tf.random_normal([n_hidden_2, n_classes]), name='W')
}

bias = {
    'b1': tf.Variable(tf.zeros([n_hidden_1]), name='b1'),
    'b2': tf.Variable(tf.zeros([n_hidden_2]), name='b2'),
    'out': tf.Variable(tf.zeros([n_classes]), name='bias')
}


# 3 构建前向网络
# 激活函数使用relu
def multilayer(x, weights, bias):
    '''
    定义前向网络函数
    '''
    layer1 = tf.add(tf.matmul(x, weights['h1']), bias['b1'], name='fc_1')
    layer1 = tf.nn.relu(layer1, name='relu_1')

    layer2 = tf.add(tf.matmul(layer1, weights['h2']), bias['b2'], name='fc_2')
    layer2 = tf.nn.relu(layer2, name='relu_2')

    out_layer = tf.add(tf.matmul(layer2, weights['out']), bias['out'], name='fc_out')

    return out_layer


# 预测函数
y_pred = multilayer(X, weights, bias)

# 4 构建损失损失函数
loss_all = tf.nn.softmax_cross_entropy_with_logits(logits=y_pred, labels=Y, name='cross_entroyp_loss')
loss = tf.reduce_mean(loss_all)

# 梯度下降优化损失函数
learning_rate = 0.001
optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(loss)

# 每批128个样例
batch_size = 128
# 一共128批
batch_n = (int)(mnist_data.train.num_examples / batch_size)

print('batch_n: %d, examples num: %d, batch size: %d' % (batch_size, mnist_data.train.num_examples, batch_size))

with tf.Session() as sess:
    #  writer = tf.summary.FileWriter('./graphs/dnn', sess.graph)

    # 初始化所有变量
    sess.run(tf.global_variables_initializer())

    loss_avg = 0
    for epoch in range(15):  # 训练15轮

        # 分batch训练
        for i in range(batch_n):
            # 获取batch数据
            batch_x, batch_y = mnist_data.train.next_batch(batch_size)

            _, l = sess.run([optimizer, loss], feed_dict={X: batch_x, Y: batch_y})
            loss_avg += l

        loss_avg = (loss_avg / batch_n)

        print('epoch: %d, loss: %f' % (epoch, loss_avg))

    print('train finished')

    # 在测试集上评估
    correct_prediction = tf.equal(tf.argmax(y_pred, 1), tf.argmax(Y, 1))
    # 计算准确率
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
    print("Accuracy:", accuracy.eval({X: mnist_data.test.images, Y: mnist_data.test.labels}))

    #  writer.close()
