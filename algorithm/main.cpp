/*
 * @Author: Gang Chen (smilechengang@qq.com)
 * @date: 2023-04-17 03:23:14
 * @last_author: Gang Chen (smilechengang@qq.com)
 * @last_edit_time: 2023-05-24 14:14:42
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// 217:存在重复元素
// 方法一：使用set，key-value一致，并且不能重复
// class Solution {
// public:
//     bool containsDuplicate(vector<int>& nums) {
//         unordered_set<int> set1;
//         for (int num : nums)
//         {
//             if(set1.find(num)!=set1.end())
//             {
//                 return true;
//             }
//             else
//             {
//                 set1.insert(num);
//             }
//         }
//         return false;
//     }
// };
// // 方法二：排序，相邻元素相等，则重复
// class Solution {
// public:
//     bool containsDuplicate(vector<int>& nums) {
//         sort(nums.begin(), nums.end());
//         for (size_t i = 1; i < nums.size(); i++)
//         {
//             if (nums[i-1] == nums[i])
//             {
//                 return true;
//             }
//         }
//         return false;
//     }
// };

// 最大子数组和
// class Solution {
// public:
//     int maxSubArray(vector<int>& nums) {
//         if (nums.empty())
//         {
//             return 0;
//         }
//         int max_sum = nums[0];
//         int sum = nums[0];
//         for (size_t i = 1; i < nums.size(); i++)
//         {
//             if(sum < 0 )
//             {
//                 sum = nums[i];
//             }
//             else
//             {
//                 sum += nums[i];
//             }
//             if (sum > max_sum)
//             {
//                 max_sum = sum;
//             }
//         }
//         return max_sum;
//     }
// };

// 两数之和
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         unordered_map<int, int> diff_map;
//         for(int i=0;i<nums.size();i++)
//         {
//             int diff = target-nums[i];
//             auto it = diff_map.find(diff);
//             if(it!=diff_map.end())
//             {
//                 vector<int> result = {it->second, i};
//                 return result
//             }
//             diff_map[nums[i]] = i;
//         }
//         return {};
//     }
// };

// 合并两个有序数组
// class Solution {
// public:
//     void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
//         vector<int> result;
//         int i,j=0;
//         while(i<m && j<n)
//         {
//             if(nums1[i]<nums2[j])
//             {
//                 result.push_back(nums1[i]);
//                 i++;
//             }
//             else if(nums1[i]==nums2[j])
//             {
//                 result.push_back(nums1[i]);
//                 result.push_back(nums2[j]);
//                 i++;
//                 j++;
//             }
//             else
//             {
//                 result.push_back(nums2[j]);
//                 j++;
//             }
//         }
//         if(i>=m && j<n)
//         {
//             for(;j<n;j++)
//             {
//                 result.push_back(nums2[j]);
//             }
//         }
//         if(j>=n&&i<m)
//         {
//             for(;i<m;i++)
//             {
//                 result.push_back(nums1[i]);
//             }
//         }
//         for (int i = 0; i < m + n; i++)
//         {
//             nums1[i] = result[i];
//         }
//         for(auto it : nums1)
//         {
//             cout << it << endl;
//         }
//     }
// };

// 128. 最长连续序列
// 方法一：排序再去重，找最长连续序列
// class Solution
// {
// public:
//     int longestConsecutive(vector<int>& nums)
//     {
//         if (nums.size() == 0)
//             return 0;
//         sort(nums.begin(), nums.end());
//         // 去重
//         auto it = unique(nums.begin(), nums.end());
//         nums.erase(it, nums.end());
//         int result = 1;
//         int count  = 1;
//         int number = nums[0];
//         for (int i = 1; i < nums.size(); i++)
//         {
//             if (number + 1 == nums[i])
//             {
//                 count++;
//                 number = nums[i];
//             }
//             else
//             {
//                 if(count>result)
//                 {
//                     result = count;

//                 }
//                 count  = 1;
//                 number = nums[i];
//             }
//         }
//         if(count>result)
//         {
//                 result = count;

//         }
//         return (count > result) ? count : result;
//     }
// };

// 借助哈希表，去重，找起始的数字（排序）
// class Solution {
// public:
//     int longestConsecutive(vector<int>& nums) {
//         int result=0;
//         unordered_set<int> nums_set;
//         for(const auto &num:nums)
//         {
//             nums_set.insert(num);
//         }

//         for(auto num:nums_set)
//         {
//             if(!nums_set.count(num-1))
//             // 寻找最开始的数字
//             {
//                 int curNum = num;
//                 int count  = 1;
//                 while(nums_set.count(curNum+1))
//                 {
//                     count++;
//                     curNum += 1;
//                 }
//                 result = max(result, count);
//             }
//         }
//         return result;
//     }
// };

// 49. 字母异位词分组
// class Solution {
// public:
//     vector<vector<string>> groupAnagrams(vector<string>& strs) {
//         unordered_map<string, vector<string>> mp;
//         for(auto str:strs)
//         {
//             string key = str;
//             sort(key.begin(), key.end());
//             mp[key].emplace_back(str);
//         }
//         vector<vector<string>> result;
//         for (auto it = mp.begin(); it != mp.end();it++)
//         {
//             result.emplace_back(it->second);
//         }
//         return result;
//     }
// };

// 283. 移动零
// 方法一，使用冒泡排序的思想
// class Solution
// {
// public:
//     void moveZeroes(vector<int>& nums)
//     {
//         if (nums.size() <= 1)
//         {
//             return;
//         }
//         for (int i = 1; i < nums.size(); i++)
//         {
//             for (int j = 0; j < nums.size() - i; j++)
//             {
//                 if (nums[j] == 0 && nums[j + 1] != 0)
//                 {
//                     int temp = nums[j];
//                     nums[j]  = nums[j + 1];
//                     nums[j + 1] = temp;
//                 }
//             }
//         }
//     }
// };

// 方法二：双指针
// class Solution {
// public:
//     void moveZeroes(vector<int>& nums) {
//         int n = nums.size(), left = 0, right = 0;
//         while (right < n) {
//             if (nums[right]) {
//                 swap(nums[left], nums[right]);
//                 left++;
//             }
//             right++;
//         }
//     }
// };

// 15. 三数之和
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> result;
        if (nums.size() < 3)
        {
            return result;
        }
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
            {
                break;
            }

            // 短路效应，放置越界访问，如果本次起始位置元素值与之前相同，则本次不比较，因为比较出来也是重复值
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            int left = i + 1, right = nums.size() - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0)
                {
                    vector<int> midResult = {nums[i], nums[left], nums[right]};
                    result.emplace_back(midResult);
                    // 结果去重
                    while (left < right && nums[left] == nums[left + 1])
                    {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1])
                    {
                        right--;
                    }
                    // 移动指针到新的不同的元素上
                    left++;
                    right--;
                }
                else if (sum < 0)
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }
        return result;
    }
};

int main()
{
    Solution solu;
    // vector<int> nums1 = {1,2,3,0,0,0};
    // vector<int> nums2 = {2,5,6};
    // int sum = 9;
    // vector<int> result;
    // solu.merge(nums1,3, nums2,3);
    // cout << result << endl;
    // vector<int> nums  = {9,1,4,7,3,-1,0,5,8,-1,6};
    // int         count = solu.longestConsecutive(nums);
    // cout << "count = " << count << endl;
    // 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
    // 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
    // vector<string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
    // vector<vector<string>> result = solu.groupAnagrams(strs);
    // vector<int> nums={0,2,0,0,3,0,12};
    // solu.moveZeroes(nums);

    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    solu.threeSum(nums);

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <algorithm>

// int main() {
//     std::vector<int> vec = {1, 2, 2, 3, 4, 4, 5, 6, 6, 6, 7};

//     // 使用 std::unique 将重复元素移动到 vector 末尾
//     auto it = std::unique(vec.begin(), vec.end());
//     cout << "it = " << *it << endl;
//     // 使用 erase 擦除重复元素
//     vec.erase(it, vec.end());

//     // 输出去重后的 vector
//     std::cout << "去重后的 vector: ";
//     for (int num : vec) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
