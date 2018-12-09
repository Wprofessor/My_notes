class Solution:
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        num = nums1 + nums2
        self.quick_sort(num, 0, len(num) - 1)
        if len(num) % 2 == 0:
            return float((num[len(num) //2] + num[len(num) // 2 - 1]) / 2)
        else:
            return float(num[len(num) // 2])

    def quick_sort(self,array, l, r):
        if l < r:
            q = self.partition(array, l, r)
            self.quick_sort(array, l, q - 1)
            self.quick_sort(array, q + 1, r)

    def partition(self,array, l, r):
        x = array[r]

        i = l - 1
        for j in range(l, r):
            if array[j] <= x:
                i += 1
                array[i], array[j] = array[j], array[i]
        array[i + 1], array[r] = array[r], array[i + 1]
        return i + 1

nums1 = [1,2]
nums2 = [3,4]
m = Solution()
print(m.findMedianSortedArrays(nums1,nums2))