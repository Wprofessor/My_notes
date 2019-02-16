def tt(x):
    del (x[2])
    return x


x = [1, 2, 3]
tt(x)
print(x)
