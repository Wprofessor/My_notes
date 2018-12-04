# 字符对应的数字作为下标
# 初始化一个255的boolean作为所有可能出现的字符对应的存在可能性，不存在重复的均为false，存在重复的，则对应的下标置为true。
# 两个指针进行移动，前指针先不动，后指针移动并根据当前字符对应整数下标是否为false或者true进行判断。
# 如果是false，则表示没有重复，则指针向后移动一位；如果为true，表示存在重复，则后指针停止移动，并计算当前字串长度，
# 且将boolean数组重置，第一个指针向前移动一位，后指针指向当前前指针。
# class Solution:
def lengthOfLongestSubstring(s):
    """
    :type s: str
    :rtype: int
    """
    count = 0
    max = count
    x = [0 for i in range(300)]  # 初始化列表为1
    for i in range(len(s)):
        for j in range(i, len(s)):
            if x[ord(s[j])] == 0:  # ord()方法为字母转数字
                x[ord(s[j])] = 1
                count += 1
            else:
                break
        if count > max:
            max = count
        count = 0
        x = [0 for i in range(300)]
    return max


# if __name__ == 'main':
#     test = Solution()
print(lengthOfLongestSubstring("a"))
