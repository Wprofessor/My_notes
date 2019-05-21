import sys, codecs
import pandas as pd
import numpy as np

a = np.random.randint(1, 100, size=[5, 5])
b = np.zeros((5,5))
xmax = a.max()
count = []
for i in range(5):
    for j in range(5):
        count.append(a[i][j])
result = sorted(count)
b[2][2] = sorted(count)[24]
b[0][0] = sorted(count)[0]
b[0][4] = sorted(count)[1]
b[4][0] = sorted(count)[2]
b[4][4] = sorted(count)[3]
val = 4
for i in range(5):
    for j in range(5):
        if result[val] not in b:
            b[i][j] = result[val]
            val += 1
print(b)
