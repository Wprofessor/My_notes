file = open("./Data/ex0.txt")
# 文件中行的长度
print(len(file.readline().split()))
print(file.readline().split()[1])
