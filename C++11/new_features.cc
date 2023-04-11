/**
 * @file new_features.cc
 * @brief To-be-added
 * @copyright Copyrightbelongs to the individual，All Rights Reserved.
 * @author Gang Chen (smilechengang@qq.com)
 * @date 2023-03-29 20:54:54
 * @last_author: Chen Gang (cheng_caft@yusur.tech)
 * @last_edit_time: 2023-03-30 10:30:40
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
    // // 字符串原始字面量
    string str1 = "D:\hode\test";
    string str2 = R"(D:\hode\test)";
    string str3 = R"test(D:\hode\test)test";
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
    cout << "str3 = " << str3 << endl;

    // nullptr
    // char *ptr1 = "ptr";
    // void *ptr2;
    // ptr1 = ptr2;
    // char *ptr = NULL;
    return 0;
}
