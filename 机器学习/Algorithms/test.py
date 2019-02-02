import numpy as np

fr = open("./Data/knn_data.txt")
num = len(fr.readlines())
returnMat = np.zeros((num, 2),dtype=float)

fr = open("./Data/knn_data.txt")
count = 0
dataLabels = []
for line in fr.readlines():
    line = line.strip()
    line = line.split()
    returnMat[count, :] = line[0:2]
    dataLabels.append(line[2])
    count += 1

