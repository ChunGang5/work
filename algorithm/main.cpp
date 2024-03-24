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
#include <queue>
#include <stack>

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
// class Solution
// {
// public:
//     vector<vector<int>> threeSum(vector<int>& nums)
//     {
//         vector<vector<int>> result;
//         if (nums.size() < 3)
//         {
//             return result;
//         }
//         sort(nums.begin(), nums.end());
//         for (int i = 0; i < nums.size(); i++)
//         {
//             if (nums[i] > 0)
//             {
//                 break;
//             }

//             // 短路效应，放置越界访问，如果本次起始位置元素值与之前相同，则本次不比较，因为比较出来也是重复值
//             if (i > 0 && nums[i] == nums[i - 1])
//             {
//                 continue;
//             }
//             int left = i + 1, right = nums.size() - 1;
//             while (left < right)
//             {
//                 int sum = nums[i] + nums[left] + nums[right];
//                 if (sum == 0)
//                 {
//                     vector<int> midResult = {nums[i], nums[left], nums[right]};
//                     result.emplace_back(midResult);
//                     // 结果去重
//                     while (left < right && nums[left] == nums[left + 1])
//                     {
//                         left++;
//                     }
//                     while (left < right && nums[right] == nums[right - 1])
//                     {
//                         right--;
//                     }
//                     // 移动指针到新的不同的元素上
//                     left++;
//                     right--;
//                 }
//                 else if (sum < 0)
//                 {
//                     left++;
//                 }
//                 else
//                 {
//                     right--;
//                 }
//             }
//         }
//         return result;
//     }
// };

// 11. 盛最多水的容器
// class Solution {
// public:
//     int maxArea(vector<int>& height) {
//         if(height.size()<=1)
//             return 0;
//         int n = height.size(), left = 0, right = n - 1;
//         int result = 0;
//         while(left < right)
//         {
//             int midArea = min(height[left], height[right]) * (right - left);
//             result      = max(result, midArea);
//             if(height[left]<height[right])
//             {
//                 left++;
//             }
//             else{
//                 right--;
//             }
//         }
//         return result;
//     }
// };

// 3. 无重复字符的最长子串
// 方法一：滑动窗口
// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         if(s.size()==0)
//             return 0;
//         if(s.size()==1)
//             return 1;

//         unordered_set<char> midSet;
//         int                 result = 0;
//         int                 n = s.size(), start = 0, end = 0;
//         for (; start < n; start++)
//         {
//             if(start!=0)
//             {
//                 // start等于0的时候set里没有任何元素
//                 midSet.erase(s[start-1]);
//             }
//             while (end < n && midSet.find(s[end])==midSet.end())
//             {
//                 // 元素不同则一直扩大右边界，知道有重复字符
//                 midSet.insert(s[end]);
//                 end++;
//             }
//             result = max(result, end - start);
//         }
//         return result;
//     }
// };
// 方法二：
// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {

//     }
// };

// 28. 找出字符串中第一个匹配项的下标
// 方法一：暴力解法
// class Solution {
// public:
//     int strStr(string haystack, string needle) {
//         if(needle.size()==0)
//             return 0;
//         int m = haystack.size(), n = needle.size();
//         for (int i = 0; i<=m-n;i++)
//         {
//             int j = i, k = 0;
//             while (k < n&&haystack[j]==needle[k])
//             {
//                 j++;
//                 k++;
//             }
//             if(k==n)
//             {
//                 return i;
//             }
//         }
//         return -1;
//     }
// };
// 方法二：KMP解法
// class Solution {
// public:
//     int strStr(string haystack, string needle) {
//         if(needle.size()==0)
//             return 0;
//         int m = haystack.size(), n = needle.size();
//         // 构建next数组
//         vector<int> nextArray(n+1);
//         nextArray[0]  = -1;
//         int         i = 0, j = -1;
//         while (i<n)
//         {
//             if(j==-1||needle[i]==needle[j])
//             {
//                 i++;
//                 j++;
//                 nextArray[i] = j;
//             }
//             else
//             {
//                 j = nextArray[j];
//             }
//         }
//         // 开始比较
//         i = 0, j = 0;
//         while(i<m&&j<n)
//         {
//             if(j==-1||haystack[i]==needle[j])
//             {
//                 i++;
//                 j++;
//             }
//             else
//             {
//                 j = nextArray[j];
//             }
//         }
//         if(j==n)
//         {
//             return i - j;
//         }
//         else
//         {
//             return -1;
//         }
//     }
// };



 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 前序遍历非递归
// class Solution {
// public:
//     vector<int> preorderTraversal(TreeNode* root) {
//         vector<int> result;
//         if(root==nullptr)
//         {
//             return result;
//         }
//         stack<TreeNode*> tree_st;
//         tree_st.push(root);
//         // cur_root更合适，其实也就是每次将一个树，通过当前的根节点划分成一个子树
//         tree_st.push(root);
//         while(!tree_st.empty())
//         {
//             TreeNode* cur_root = tree_st.top();
//             result.emplace_back(cur_root->val);
//             tree_st.pop();
//             if(cur_root->right)
//             {
//                 tree_st.push(cur_root->right);
//             }
//             if(cur_root->left)
//             {
//                 tree_st.push(cur_root->right);
//             }
//         }
//         return result;
//     }
// };

// // 层序遍历
// class Solution {
// public:
//     vector<vector<int>> levelOrder(TreeNode* root) {
//         vector<vector<int>> result;
//         if(root == nullptr)
//         {
//             return result;
//         }
//         queue<TreeNode*> tree_queue;
//         tree_queue.push(root);
//         while(!tree_queue.empty())
//         {
//             vector<int> temp_vec;
//             for(int i =0;i<tree_queue.size();i++)
//             {
//                 TreeNode* cur_root=tree_queue.front();
//                 tree_queue.pop();
//                 temp_vec.emplace_back(cur_root->val);
//                 if(cur_root->left!=nullptr)
//                 {
//                     tree_queue.push(cur_root->left);
//                 }
//                 if(cur_root->right!=nullptr)
//                 {
//                     tree_queue.push(cur_root->right);
//                 }
//             }
//             result.emplace_back(temp_vec);

//         }
//         return result;
//     }

// };

// 队列加数组逆序的方式更好
// class Solution {
// public:
//     vector<vector<int>> levelOrderBottom(TreeNode* root) {
//         vector<vector<int>> result;
//         if(root==nullptr)
//         {
//             return result;
//         }
//         stack<vector<TreeNode*>> st;
//         queue<TreeNode*> qt;
//         qt.push(root);
//         while(!qt.empty())
//         {
//             vector<TreeNode*> vector_temp;
//             int size=qt.size();
//             for(int i=0;i<size;i++)
//             {
//                 TreeNode* cur_root=qt.front();
//                 qt.pop();
//                 vector_temp.emplace_back(cur_root);
//                 if(cur_root->left)
//                 {
//                     qt.push(cur_root->left);
//                 }
//                 if(cur_root->right)
//                 {
//                     qt.push(cur_root->right);
//                 }
//             }
//             st.push(vector_temp);
//         }
//         while (!st.empty())
//         {
//             vector<TreeNode*> vec_temp = st.top();
//             st.pop();
//             vector<int> result_temp;
//             for(auto& t: vec_temp)
//             {
//                 result_temp.emplace_back(t->val);
//             }
//             result.emplace_back(result_temp);
//         }
        
//         return result;
//     }
// };
// #include<stack>
// int main()
// {
//     Solution solu;
//     // vector<int> nums1 = {1,2,3,0,0,0};
//     // vector<int> nums2 = {2,5,6};
//     // int sum = 9;
//     // vector<int> result;
//     // solu.merge(nums1,3, nums2,3);
//     // cout << result << endl;
//     // vector<int> nums  = {9,1,4,7,3,-1,0,5,8,-1,6};
//     // int         count = solu.longestConsecutive(nums);
//     // cout << "count = " << count << endl;
//     // 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
//     // 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
//     // vector<string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
//     // vector<vector<string>> result = solu.groupAnagrams(strs);
//     // vector<int> nums={0,2,0,0,3,0,12};
//     // solu.moveZeroes(nums);
//     // vector<int> nums = {-1, 0, 1, 2, -1, -4};
//     // solu.threeSum(nums);
//     // vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
//     // solu.maxArea(height);
//     // string str="abcabcbb";
//     // solu.lengthOfLongestSubstring(str);
//     // string haystack = "leetcode", needle = "leeto";
//     // cout << solu.strStr(haystack, needle) << endl;
    
//     TreeNode* cur15=new TreeNode(15);
//     TreeNode* cur7 = new TreeNode(7);
//     auto cur20=new TreeNode(20,cur15,cur7);
//     auto cur9=new TreeNode(9);
//     TreeNode* root = new TreeNode(3, cur9,cur20);
//     solu.levelOrderBottom(root);
    

//         return result;
//     }
// };

// 二叉树的右视图
// class Solution {
// public:
//     vector<int> rightSideView(TreeNode* root) {
//         vector<int> result;
//         if(root==nullptr)
//         {
//             return result;
//         }
//         queue<TreeNode*> queue_tr;
//         queue_tr.push(root);
//         while(!queue_tr.empty())
//         {
//             int size=queue_tr.size();
//             for(int i=0;i<size;i++)
//             {
//                 TreeNode* cur=queue_tr.front();
//                 queue_tr.pop();
//                 if(cur->left)
//                 {
//                     queue_tr.push(cur->left);
//                 }
//                 if(cur->right)
//                 {
//                     queue_tr.push(cur->right);
//                 }
//                 if(size-i<=1)
//                 {
//                     result.emplace_back(cur->val);;
//                 }
//             }
//         }
//         return result;
//     }
// };
// #include<stack>
// int main()
// {
//     Solution solu;
//     // vector<int> nums1 = {1,2,3,0,0,0};
//     // vector<int> nums2 = {2,5,6};
//     // int sum = 9;
//     // vector<int> result;
//     // solu.merge(nums1,3, nums2,3);
//     // cout << result << endl;
//     // vector<int> nums  = {9,1,4,7,3,-1,0,5,8,-1,6};
//     // int         count = solu.longestConsecutive(nums);
//     // cout << "count = " << count << endl;
//     // 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
//     // 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
//     // vector<string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
//     // vector<vector<string>> result = solu.groupAnagrams(strs);
//     // vector<int> nums={0,2,0,0,3,0,12};
//     // solu.moveZeroes(nums);
//     // vector<int> nums = {-1, 0, 1, 2, -1, -4};
//     // solu.threeSum(nums);
//     // vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
//     // solu.maxArea(height);
//     // string str="abcabcbb";
//     // solu.lengthOfLongestSubstring(str);
//     // string haystack = "leetcode", needle = "leeto";
//     // cout << solu.strStr(haystack, needle) << endl;

//     TreeNode* cur15=new TreeNode(15);
//     TreeNode* cur7 = new TreeNode(7);
//     auto cur20=new TreeNode(20,cur15,cur7);
//     auto cur9=new TreeNode(9);
//     TreeNode* root = new TreeNode(3, cur9,cur20);
//     solu.rightSideView(root);

//     return 0;
// }

// #include <iostream>
// #include <string>
// using namespace std;

// // int main() {
// //     string str;
// //     while(getline(cin,str))
// //     {
// //         cout<<"size = "<<str.size()<<endl;
// //         int n=0,flag=1;
// //         for(int i=str.size()-1;i>=0;i--)
// //         {
// //             if(str[i]==' ')
// //             {
// //                 cout<<"i = "<<i<<endl;
// //                 n=str.size()-i-1;
// //                 break;
// //             }
// //         }
// //         cout<<n<<endl;
// //     }
// //     return 0;
// // }
// #include "test.h"
// // void test()
// // {
// //     int a=1,b=2;
// //     cout<<Add(a,b)<<endl;
// // }

// #include<cmath>
// int main() 
// {
//     // string str;
//     // while(getline(cin,str))
//     // {
//     //     int len=str.length();
//     //     if(len%8!=0)
//     //     {
//     //         int count = 8 - len%8;
//     //         str.append(count,'0');
//     //     }
//     //     // int newLen=str.length();
//     //     int newLen = 0;
//     //     for(int i=0;i<str.length();i+=8)
//     //     {
//     //         cout<<str.substr(i,8)<<endl;
//     //     }
//     // }

//     string str = "dhaiuwfhuaihf";
//     string str1=str.substr(3,2);
//     cout<<str1<<endl;
//     str.append(2,'c');
//     cout<<str<<endl;

//     int sum = pow(16.0,1);
//     cout<<sum<<endl;
//     //test();
//     //cout<<Add(3,2)<<endl;
//     return 0;
// }

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

// int main(){
//     long n;
//     cin >> n;
//     for(long i = 2; i <= sqrt(n) && i <= n; i++){  //从小到大的质因子，质因子不会超过它的开方
//         while(n % i == 0){ //所有的质数前面全部除掉，后续就不会有合因子
//             cout << i << " ";
//             n /= i; //除掉质因子
//         }
//     }
//     if(n - 1) //自己本身就是质数
//         cout << n << " ";
//     return 0;
// }

// class test
// {
// public:
//     int test1()
//     {
//         return 1;
//     }
//     static int test2()
//     {
//         return 2;
//     }
// private:
//     int a;
// };

// int main()
// {
//     int a=2;
//     int& b=a;
//     b--;
//     cout<<b<<endl;
//     test t;
//     cout<<t.test2()<<endl;;
//     return 0;
// }


// 迭代器失效问题正确写法
// int main() {
//     vector<int> v;
// 	v.push_back(1);
// 	v.push_back(2);
// 	v.push_back(3);
// 	v.push_back(4);
// 	auto it = v.begin();
//     while(it!=v.end())
//     {
//         if(*it%2==0)
//         {
//             it=v.erase(it);
//         }
//         else
//         {
//             it++;
//         }
//     }
//     for(auto& i:v)
//     {
//         cout<<i<<endl;
//     }
//     return 0;
// }

// 句子逆序
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <string.h>
// using namespace std;

// int main() {
//     vector<string> vec;
//     string str="I am a boy";
//     //strlen(str.c_str());
//     int i=0,j=0;
//     string str_fix;
//     // strlen(c库的函数,接受C风格的字符串) size都计算的有效长度，sizeof关键字计算包含\0
//     while(j <= str.size() && i<=j)  //j要等于str.size()，不然到不可\0那一步
//     {
//         if(str[j]!=' ' || str[j]=='\n')
//         {
//             j++;
//         }
//         else 
//         {
//             str_fix=str.substr(i,j-i);
//             vec.emplace_back(str_fix);
//             j++;
//             i=j;
//         }
//     }
//     reverse(vec.begin(),vec.end());
//     i=0;
//     for(;i<vec.size()-1;i++)
//     {
//         cout<<vec[i]<<" ";
//     }
//     cout<<vec[i]<<endl;
//     return 0;
// }

#include <iostream>
#include <forward_list>
#include <algorithm>
using namespace std;

int main() {
    int num;
    cin>>num;
    int head_val;
    cin>>head_val;
    forward_list<int> list;
    list.push_front(head_val);
    for(int i =1;i<num;i++)
    {
        int front,back;
        cin>>back>>front;
        auto it=find(list.begin(),list.end(),front);
        list.insert_after(it,back);
    }
    int last;
    cin>>last;
    list.remove(last);
    for(auto it:list)
    {
        cout<<it<<" ";
    }
    cout<<endl;
    return 0;
}