import random

data = [[1, 4, 1], [0.5, 2, 1], [2, 2.3, 1], [1, 0.5, -1], [2, 1, -1],
            [4, 1, -1], [3.5, 4, 1], [3, 2.2, -1]]
x = random.randint(0,len(data))
y = data[x]
print(y)