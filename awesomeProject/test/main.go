package main

import (
	"fmt"
	"math"
)

func merge(nums1 []int, m int, nums2 []int, n int) []int {
	if m == 0 {
		return nums2
	}
	if n == 0 {
		return nums1
	}
	nums := make([]int, 0)
	var minLen int
	if m < n {
		minLen = m
	} else {
		minLen = n
	}
	for i := 0; i < minLen; i++ {
		if nums1[i] < nums2[i] {
			nums = append(nums, nums1[i])
			nums = append(nums, nums2[i])
		} else {
			nums = append(nums, nums2[i])
			nums = append(nums, nums1[i])
		}

	}
	if m == n {
		return nums
	}
	if m > minLen {
		for i := 0; i < m-minLen; i++ {
			nums = append(nums, nums1[minLen+i])
		}

	} else {
		for i := 0; i < n-minLen; i++ {
			nums = append(nums, nums2[minLen+i])
		}
	}
	return nums
}

func maxSubSum(arr []int, left, right int) float64 {
	if left == right {
		if arr[left] > 0 {
			return float64(arr[left])
		} else {
			return 0
		}
	}
	center := left + (right-left)/2
	maxLeftSum := maxSubSum(arr, left, center)
	maxRightSum := maxSubSum(arr, center+1, right)
	maxleftBorderSum, maxRightBorderSum := 0, 0
	leftBorderSum, rightBorderSum := 0, 0
	for i := center; i >= left; i-- {
		leftBorderSum += arr[i]
		if leftBorderSum > maxleftBorderSum {
			// 这块注意一下，从后往前找，找要连接的left段最大的子序列和
			maxleftBorderSum = leftBorderSum
		}
	}
	for i := center + 1; i <= right; i++ {
		// 这块从前往后找，找要连接的right段最大子序列和
		rightBorderSum += arr[i]
		if rightBorderSum > maxRightBorderSum {
			maxRightBorderSum = rightBorderSum
		}
	}
	// 这块找到要连接的left段最大子序列和和要连接的right段最大子序列和，相加起来再与left段最大子序列和和right段最大子序列和相比较，找出最大的
	max1 := math.Max(float64(maxLeftSum), float64(maxRightSum))
	return math.Max(float64(maxleftBorderSum+maxRightBorderSum), max1)
}
func maxSubsequenceSum(arr []int, n int) int {
	sum, maxSum := 0, 0
	for i := 0; i < n; i++ {
		sum += arr[i]
		if sum > maxSum {
			maxSum = sum
		} else if sum < 0 {
			// 之前的和现在已经是负数了，那么就将之前的舍弃，从下一个数开始找，因为负数加任何数都比那个数小
			sum = 0
		}
	}
	return maxSum
}

var famp []int

func longestPalindrome(s string) string {
	if len(s) == 1 {
		return s
	}
	if len(s) == 2 && s[0] == s[1] {
		return s[0:]
	}
	var middle, left, right int
	if len(s)%2 == 0 {
		middle = len(s) / 2
		left = middle - 1
		right = middle
	} else {
		middle = len(s) / 2
		left = middle
		right = middle
	}
	for left > 0 && right <= len(s) {
		if s[left] == s[right] {
			left--
			right++
		} else {
			break
		}
	}
	return s[left+1 : right]
}
func main() {
	//fmt.Println(famp)
	//arr := []int{4, -3, 5, -2, -1, 2, 6, -2}
	////result := maxSubSum(arr, 0, len(arr)-1)
	//result := maxSubsequenceSum(arr, len(arr))
	//fmt.Println(result)
	//var a, b , c int
	//a = b = c
	//fmt.Println(a,b,c)
	str := "ccc"
	//s := longestPalindrome(str)
	s := countSubstrings(str)
	fmt.Println(s)
}

//从左往右扫一遍字符串，以每个字符做轴，用中心扩散法，依次遍历计数回文子串。
func countSubstrings(s string) int {
	res := 0
	for i := 0; i < len(s); i++ {
		res += countPalindrome(s, i, i)
		res += countPalindrome(s, i, i+1)
	}
	return res
}

func countPalindrome(s string, left, right int) int {
	res := 0
	for left >= 0 && right < len(s) {
		if s[left] != s[right] {
			break
		}
		left--
		right++
		res++
	}
	return res
}
