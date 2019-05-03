import tensorflow as tf

# 声明w1 w2 两个变量
w1 = tf.Variable(tf.random_normal((2, 3), stddev=1, seed=1))
w2 = tf.Variable(tf.random_normal((3, 1), stddev=1, seed=1))

x = tf.placeholder(tf.float32, shape=(3, 2), name="input")

a = tf.matmul(x, w1)
y = tf.matmul(a, w2)

# 会话
sess = tf.Session()

# 初始化两个变量
# sess.run(w1.initializer)
# sess.run(w2.initializer)
# 等价于上面两个
init_op = tf.global_variables_initializer()
sess.run(init_op)

# feed_dict来指定x的取值
print(sess.run(y, feed_dict={x: [[0.7, 0.9], [0.1, 0.4], [0.5, 0.8]]}))
sess.close()
