def find_MaxCrossSubArray(A, low, mid, high):
    leftMaxSum = mid
    leftSum = mid
    leftIndex = mid
    # 找中点左边的最大字串和
    for i in range(mid - 1, low - 1, -1):
        leftSum += A[i]
        if leftSum > leftMaxSum:
            leftMaxSum = leftSum
            leftIndex = i
    rightMaxSum = 0
    rightSum = 0
    rightIndex = mid
    # 找中点右边的最大字串和
    for i in range(mid + 1, high + 1):
        rightSum += A[i]
        if rightSum > rightMaxSum:
            rightMaxSum = rightSum
            rightIndex = i
    # 跨中点的最大字串之和
    MaxSum = rightMaxSum + leftMaxSum
    return MaxSum, leftIndex, rightIndex


def find_MaxSubArray(A, low, high):
    if low == high:
        return A[low], low, high
    mid = (low + high) // 2
    # 递归分别求左边，右边，跨中点的最大字串之和
    leftSum, left_low, left_high = find_MaxSubArray(A, low, mid)
    rightSum, right_low, right_high = find_MaxSubArray(A, mid + 1, high)
    crossSum, cross_low, cross_high = find_MaxCrossSubArray(A, low, mid, high)
    if leftSum >= rightSum and leftSum >= crossSum:
        return leftSum, left_low, left_high
    elif rightSum >= leftSum and rightSum >= crossSum:
        return rightSum, right_low, right_high
    else:
        return crossSum, cross_low, cross_high


A = [13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7]
print(find_MaxSubArray(A, 0, len(A) - 1))
