class Solution:
    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        dit = {}
        dit["I"] = 1
        dit["V"] = 5
        dit["X"] = 10
        dit["L"] = 50
        dit["C"] = 100
        dit["D"] = 500
        dit["M"] = 1000
        m = 0
        for i in range(len(s)):
            if i < len(s) - 1 and s[i] < s[i + 1]:

                m = m - dit[s[i]]
            else:
                m = m + dit[s[i]]
        return abs(m)


if __name__ == "__main__":
    mod = Solution()
    print(mod.romanToInt("MCMXCIV"))
