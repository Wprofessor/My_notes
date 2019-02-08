class Solution:
    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        left = 0
        right = len(height) - 1
        vmax = min(height[left], height[right]) * (right - left)
        while left < right:
            vmax = max(vmax, min(height[left], height[right]) * (right - left))
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        return vmax


if __name__ == "__main__":
    model = Solution()
    print(model.maxArea([1, 8, 6, 2, 5, 4, 8, 3, 7]))
