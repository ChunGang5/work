/*
 * @Author: Gang Chen (smilechengang@qq.com)
 * @date: 2023-04-17 03:23:14
 * @last_author: Gang Chen (smilechengang@qq.com)
 * @last_edit_time: 2023-05-24 14:14:42
 */
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

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
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) { 
        vector<int> result;
        int i,j=0;
        while(i<m && j<n)
        {
            if(nums1[i]<nums2[j])
            {
                result.push_back(nums1[i]);
                i++;
            }
            else if(nums1[i]==nums2[j])
            {
                result.push_back(nums1[i]);
                result.push_back(nums2[j]);
                i++;
                j++;
            }
            else
            {
                result.push_back(nums2[j]);
                j++;
            }
        }
        if(i>=m && j<n)
        {
            for(;j<n;j++)
            {
                result.push_back(nums2[j]);
            }
        }
        if(j>=n&&i<m)
        {
            for(;i<m;i++)
            {
                result.push_back(nums1[i]);
            }
        }
        for (int i = 0; i < m + n; i++)
        {
            nums1[i] = result[i];
        }
        for(auto it : nums1)
        {
            cout << it << endl;
        }
    }
};

int main()
{
    Solution solu;
    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};
    int sum = 9;
    vector<int> result;
    solu.merge(nums1,3, nums2,3);
    //cout << result << endl;
    return 0;
}