import numpy as np

# fr = open('C:\\Users\\王教授\\Desktop\\test1.txt')
# dataset = []
#
# for line in fr.readlines():
#     line = line.strip().split(',')
#     #temp = line.split(',')
#     # temp = str(temp).strip()
#     dataset.append(line)
# print(dataset)
# fr = open('C:\\Users\\王教授\\Desktop\\test2.txt')
# dataset = []
# label = []
# for line in fr.readlines():
#     line = line.strip().split()
#     dataset.append(line[1:-1])
#     label.append(int(line[-1]))
# print(dataset)
# print(label)
fr = open('C:\\Users\\王教授\\Desktop\\preditData.txt')
Inputdata = []
kinds = []
for line in fr.readlines():
    line = line.strip().split()
    print(line[0])
   # kinds.append(str(line[0]))
    Inputdata.append(line[1:])
print(Inputdata, '\n', kinds)
