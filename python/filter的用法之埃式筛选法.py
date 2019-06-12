# filter()的作用是从一个序列中筛出符合条件的元素。
# 由于filter()使用了惰性计算，所以只有在取filter()结果的时候，才会真正筛选并每次返回下一个筛出的元素。

# 素数筛选之埃式筛选法

# 返回一个函数用于辅助筛选
def _not_divisible(n):
    return lambda x: x % n > 0


# 构造一个从3开始的无限奇数序列
# 注意是生成器
def _odd_iter():
    n = 1
    while True:
        n = n + 2
        yield n

# 注意filter中第二个参数是可迭代对象（可以直接使用 for 循环进行遍历的对象）
def primes():
    yield 2
    it = _odd_iter()  # 初始序列
    while True:
        n = next(it)  # 返回序列的第一个数
        yield n
        it = filter(_not_divisible(n), it)  # 构造新序列


for n in primes():
    if n < 1000:
        print(n)
    else:
        break
