class Solution:
    def isPalindrome(self,x):
        word = str(x)
        count = len(word)
        for i in range(count//2):
            if word[i] != word[count - i - 1]:
                return False
        return True
wjh = Solution()
print(wjh.isPalindrome("101"))
