/**
 * @file new_features.cc
 * @brief To-be-added
 * @copyright Copyrightbelongs to the individual，All Rights Reserved.
 * @author Gang Chen (smilechengang@qq.com)
 * @date 2023-03-29 20:54:54
 * @last_author: Please set LastEditors
 * @last_edit_time: 2023-04-19 17:47:52
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// int main()
// {
//     // // 字符串原始字面量
//     // string str1 = "D:\hode\test";
//     // string str2 = R"(D:\hode\test)";
//     // string str3 = R"test(D:\hode\test)test";
//     // cout << "str1 = " << str1 << endl;
//     // cout << "str2 = " << str2 << endl;
//     // cout << "str3 = " << str3 << endl;

//     // nullptr
//     // char *ptr1 = "ptr";
//     // void *ptr2;
//     // ptr1 = ptr2;
//     // char *ptr = NULL;

//     if (1 && 3)
//     {
//         cout << "test" << endl;
//     }
//     return 0;
// }


// #include <iostream>
// #include <string>
// #include <unordered_map>

// struct Person {
//     std::string name;
//     int age;

//     bool operator==(const Person& other) const {
//         return name == other.name && age == other.age;
//     }
// };

// namespace std {
//     template<>
//     struct hash<Person> {
//         size_t operator()(const Person& p) const {
//             return hash<string>()(p.name) ^ hash<int>()(p.age);
//         }
//     };
// }

// int main() {
//     std::unordered_map<Person, int> ages = {
//         {{"Alice", 30}, 30},
//         {{"Bob", 40}, 40},
//         {{"Charlie", 50}, 50}
//     };

//     Person p1 = {"Alice", 30};
//     auto it = ages.find(p1);
//     if (it != ages.end()) {
//         std::cout << p1.name << " is " << it->second << " years old.\n";
//     } else {
//         std::cout << "Person not found.\n";
//     }

//     Person p2 = {"David", 20};
//     it = ages.find(p2);
//     if (it != ages.end()) {
//         std::cout << p2.name << " is " << it->second << " years old.\n";
//     } else {
//         std::cout << "Person not found.\n";
//     }

//     return 0;
// }

#include <boost/lockfree/spsc_queue.hpp>
#include <iostream>

int main()
{
    boost::lockfree::spsc_queue<int, boost::lockfree::capacity<1024>> queue;

    // 生产者线程
    std::thread producer([&] {
        for (int i = 0; i < 1000; ++i) {
            while (!queue.push(i)); // 等待队列可用
        }
    });

    // 消费者线程
    std::thread consumer([&] {
        int value;
        for (int i = 0; i < 1000; ++i) {
            while (!queue.pop(value)); // 等待队列非空
            std::cout << value << std::endl;
        }
    });

    producer.join();
    consumer.join();
}
