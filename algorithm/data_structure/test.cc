/*
 * @Author: Gang Chen (smilechengang@qq.com)
 * @date: 2023-04-17 03:23:14
 * @last_author: Gang Chen (smilechengang@qq.com)
 * @last_edit_time: 2023-04-23 06:52:34
 */
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// 217:存在重复元素
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> set1;
        for (int num : nums)
        {
            if(set1.find(num)!=set1.end())
            {
                return true;
            }
            else 
            {
                set1.insert(num);
            }
        }
        return false;
    }
};
int main()
{
    Solution solu;
    vector<int> nums = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    bool flag = solu.containsDuplicate(nums);
    cout << flag << endl;
    
    return 0;
}