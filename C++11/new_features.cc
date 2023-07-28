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
// struct GreaterThan {
//     int threshold;

//     GreaterThan(int threshold) : threshold(threshold) {}

//     bool operator()(int value) {
//         return value > threshold;
//     }
// };

// int main() {
//     std::vector<int> numbers = {5, 10, 15, 20, 25, 30};
//     int threshold = 15;

//     // 使用仿函数作为算法的参数
//     auto result = std::count_if(numbers.begin(), numbers.end(), GreaterThan(threshold));

//     std::cout << "Numbers greater than " << threshold << ": " << result << std::endl;

//     return 0;
// }

// lambda表达式
// int main()
// {
//     int a = 10;
//     auto f = [=](){ return a; };
//     auto f1 = [&]() { return ++a; }; // return 的三个步骤，如果是后置++，return会先把原始值抛出来，再++
//     std::cout << "a = " << f() << std::endl;
//     std::cout << "a = " << f1() << std::endl;
// }

#include <memory>
// int main()
// {
//     std::shared_ptr<int> ptr (new int(1));
//     int*                 p = ptr.get();
//     std::cout << "p = " << p << "data = " << *p << std::endl;
//     int* p2 = new int[10];
//     std::shared_ptr<int> ptr1(p2);
//     std::shared_ptr<int> ptr2 = ptr1;
//     //auto ptr3 = std::make_shared<int>(10);
//     std::weak_ptr<int> wp(ptr1);
//     std::cout << "use count = " << wp.use_count() << std::endl;
// }

struct A;struct B;
struct A {
    std::shared_ptr<B> bptr;
    ~A() {
        std::cout << "A delete" << std::endl;
    }
    void Print() {
        std::cout << "A" << std::endl;
    }
};
struct B {
    std::weak_ptr<A> aptr; // 这里改成weak_ptr
    ~B() {
        std::cout << "B delete" << std::endl;
    }
    void PrintA() {
        if (!aptr.expired()) { // 监视shared_ptr 的生命周期
            auto ptr = aptr.lock();
            ptr->Print();
        }
    }
};
int main() {
    auto aaptr = std::make_shared<A>();
    auto bbptr = std::make_shared<B>();
    std::weak_ptr<A> wpa(aaptr);
    std::weak_ptr<B> wpb(bbptr);
    std::cout << "aaptr use count = " << wpa.use_count() << std::endl;
    std::cout << "bbptr use count = " << wpb.use_count() << std::endl;
    aaptr->bptr = bbptr;
    bbptr->aptr = aaptr;
    std::cout << "aaptr use count = " << wpa.use_count() << std::endl;
    std::cout << "bbptr use count = " << wpb.use_count() << std::endl;
    bbptr->PrintA();
    return 0;
}
#define GUARD(P) std::shared ptr<void> p##p(p[](void*p)(GetHandle()->Release(p);l);
void* p= GetHandle()->Create();
GUARD(p);// 安全
