/**
 * @file new_features.cc
 * @brief To-be-added
 * @copyright Copyrightbelongs to the individual，All Rights Reserved.
 * @author Gang Chen (smilechengang@qq.com)
 * @date 2023-03-29 20:54:54
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

//using namespace std;

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

// #include <boost/lockfree/spsc_queue.hpp>
// #include <iostream>

// int main()
// {
//     boost::lockfree::spsc_queue<int, boost::lockfree::capacity<1024>> queue;

//     // 生产者线程
//     std::thread producer([&] {
//         for (int i = 0; i < 1000; ++i) {
//             while (!queue.push(i)); // 等待队列可用
//         }
//     });

//     // 消费者线程
//     std::thread consumer([&] {
//         int value;
//         for (int i = 0; i < 1000; ++i) {
//             while (!queue.pop(value)); // 等待队列非空
//             std::cout << value << std::endl;
//         }
//     });

//     producer.join();
//     consumer.join();
// }

// void output(int i, int j);
// int main()
// {
//     std::function<void(int,int)> f = output;
//     auto                     f2 = std::bind(output, std::placeholders::_2,2);
//     f(1,2);
//     f2(1,2);
//     return 0;
// }

// void output(int i, int j)
// {
//     std::cout << i << j << std::endl;
// }

#include <iostream>
#include <vector>
#include <algorithm>

// 仿函数类
struct GreaterThan {
    int threshold;

    GreaterThan(int threshold) : threshold(threshold) {}

    bool operator()(int value) {
        return value > threshold;
    }
};

int main() {
    std::vector<int> numbers = {5, 10, 15, 20, 25, 30};
    int threshold = 15;

    // 使用仿函数作为算法的参数
    auto result = std::count_if(numbers.begin(), numbers.end(), GreaterThan(threshold));

    std::cout << "Numbers greater than " << threshold << ": " << result << std::endl;

    return 0;
}
