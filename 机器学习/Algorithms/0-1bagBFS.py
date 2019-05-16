import numpy as np
import queue
import math

w = [3, 5, 2, 1]
v = [9, 10, 7, 4]


def TestBag(V):
    vec_len = 2 ** (len(v) + 1) - 1  # 树的大小
    vec_v = np.zeros(vec_len)   # 每个节点的价值
    vec_w = np.zeros(vec_len)   # 每个节点的重量
    vec_w[0] = V
    que = queue.Queue()
    que.put(0)
    best = 0
    while not que.empty():
        current = que.get()
        level = int(math.log(current + 1, 2))
        if vec_v[current] > vec_v[best]:
            best = current

        left = 2 * current + 1  # 左孩子的索引
        right = 2 * current + 2  # 右孩子的索引

        if left < vec_len and vec_w[current] - w[level] > 0 and vec_v[current] + v[level] > vec_v[best]:
            vec_v[left] = int(vec_v[current] + v[level])
            vec_w[left] = vec_w[current] - w[level]
            que.put(left)
        if right < vec_len and sum(v[level + 1:-1]) + vec_v[current] > vec_v[best]:
            vec_v[right] = vec_v[current]
            vec_w[right] = vec_w[current]
            que.put(right)
    print('价值最大为：', vec_v[best])


if __name__ == '__main__':
    print('请输入背包容量：')
    captical = input()
    TestBag(captical)
