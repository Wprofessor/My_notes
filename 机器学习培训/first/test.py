def longestPalindrome(s):
    judge = [[0]*len(s) for i in range(len(s))] #初始化二维数组
    m = 0
    # s1 = s[0]
    s1 = []
    if s == "":
        return ""
    for i in range(len(s)):
        judge[i][i] = 1
        for j in range(i+1):
            if s[i] == s[j] and (i - j < 2 or (i > 0 and judge[j+1][i-1] == 1)):
                judge[j][i] = 1
            else:
                judge[j][i] = 0
            if judge[j][i] == 1:
                if (i - j + 1) > m:
                    m = i - j + 1
                    s1 = s[j:i+1]
    return s1
print(longestPalindrome(""))

