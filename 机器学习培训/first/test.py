import numpy as np

group = np.array([
    [1.0, 0.9],
    [1.0, 1.0],
    [0.1, 1.2],
    [0.0, 100]
])
minVals = group.min(0)
maxVals = group.max(1)
print(minVals)