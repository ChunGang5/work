/*
 * @Author: Gang Chen (smilechengang@qq.com)
 * @date: 2023-04-17 03:23:14
 * @last_author: Gang Chen (smilechengang@qq.com)
 * @last_edit_time: 2023-05-24 00:04:54
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
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty())
        {
            return 0;
        }
        int max_sum = nums[0];
        int sum = nums[0];
        for (size_t i = 1; i < nums.size(); i++)
        {
            if(sum < 0 )
            {
                sum = nums[i];
            }
            else
            {
                sum += nums[i];
            }
            if (sum > max_sum)
            {
                max_sum = sum;
            }
        }
        return max_sum;
    }
};
int main()
{
    Solution solu;
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    int flag = solu.maxSubArray(nums);
    cout << flag << endl;

    return 0;
}