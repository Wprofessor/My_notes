import random
import numpy as np
import matplotlib.pyplot as plt
data = [[1, 4, 1], [0.5, 2, 1], [2, 2.3, 1], [1, 0.5, -1], [2, 1, -1],
            [4, 1, -1], [3.5, 4, 1], [3, 2.2, -1]]
x1 = []
y1 = []
x2 = []
y2 = []
for p in data:
    if p[2] > 0:
        x1.append(p[0])
        y1.append(p[1])
    else:
        x2.append(p[0])
        y2.append(p[1])
x1 = np.array(x1)
x2 = np.array(x2)
y1 = np.array(y1)
y2 = np.array(y2)
plt.scatter(x1, y1, label="y = 1")
plt.scatter(x2, y2, label="y = -1")
plt.legend()
plt.xlabel('X1')
plt.ylabel('X2')
plt.show()