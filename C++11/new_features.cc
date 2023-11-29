/**
 * @file new_features.cc
 * @brief To-be-added
 * @copyright Copyrightbelongs to the individual，All Rights Reserved.
 * @author Gang Chen (smilechengang@qq.com)
 * @date 2023-03-29 20:54:54
 */

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

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

#include <algorithm>
#include <iostream>
#include <vector>

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

// struct A;struct B;
// struct A {
//     std::shared_ptr<B> bptr;
//     ~A() {
//         std::cout << "A delete" << std::endl;
//     }
//     void Print() {
//         std::cout << "A" << std::endl;
//     }
// };
// struct B {
//     std::weak_ptr<A> aptr; // 这里改成weak_ptr
//     ~B() {
//         std::cout << "B delete" << std::endl;
//     }
//     void PrintA() {
//         if (!aptr.expired()) { // 监视shared_ptr 的生命周期
//             auto ptr = aptr.lock();
//             ptr->Print();
//         }
//     }
// };
// int main() {
//     auto aaptr = std::make_shared<A>();
//     auto bbptr = std::make_shared<B>();
//     std::weak_ptr<A> wpa(aaptr);
//     std::weak_ptr<B> wpb(bbptr);
//     std::cout << "aaptr use count = " << wpa.use_count() << std::endl;
//     std::cout << "bbptr use count = " << wpb.use_count() << std::endl;
//     aaptr->bptr = bbptr;
//     bbptr->aptr = aaptr;
//     std::cout << "aaptr use count = " << wpa.use_count() << std::endl;
//     std::cout << "bbptr use count = " << wpb.use_count() << std::endl;
//     bbptr->PrintA();
//     return 0;
// }
// #define GUARD(P) std::shared ptr<void> p##p(p[](void*p)(GetHandle()->Release(p);l);
// void* p= GetHandle()->Create();
// GUARD(p);// 安全

// class Test
// {
//     int a;
//     inline void print()
//     {
//         std::cout << a << std::endl;
//     }
// };

// struct Test2
// {
//     int a;
//     void a_add()
//     {
//         a++;
//     }
// private:
//     int b;
//     void b_add()
//     {
//         b++;
//     }
// };

// int main()
// {
//     Test test;
//     std::cout << sizeof(test) << std::endl;
//     Test2 test2;
//     test2.a_add();
//     static int foo;
//     extern int foo;
// }

// int main()
// {
//     int a = 1, b = 0;
//     decltype(a + b) c;
//     decltype(a += b) d = c;
//     //d                  = 20;
//     std::cout << "c = " << c << std::endl;
//     int e = 0;
//     int &f = e;
//     int *p = nullptr;
//     f      = 10;
//     std::cout << "e = " << e << std::endl;
//     return 0;
// }

// class A
// {
// public:
//     A():m_ptr(new int(0))
//     {
//         std::cout << "construct" << std::endl;
//     }
//     // A(const A& a):m_ptr(new int(5))
//     // {
//     //     std::cout << "copy construct" << std::endl;
//     // }
//     A(A &&a):m_ptr(a.m_ptr)
//     {
//         a.m_ptr = nullptr;
//         std::cout << "move construct" << std::endl;
//     }
//     ~A()
//     {
//         std::cout << "destruct" << std::endl;
//         delete m_ptr;
//     }
// private:
//     int* m_ptr;
// };

// A Get(bool flag)
// {
//     A a;
//     A b;
//     if(flag)
//     {
//         return a;
//     }
//     else
//     {
//         return b;
//     }
// }
// int main()
// {
//     A a = Get(false);
//     return 0;
// }

// class A
// {
// public:
//     A(int size) : size_(size)
//     {
//         data_ = new int[size];
//         std::cout << "construct1" << std::endl;
//     }
//     A()
//     {
//         std::cout << "construct2" << std::endl;
//     }
//     A(const A& a)
//     {
//         size_ = a.size_;
//         data_ = new int[size_];
//         std::cout << "copy " << std::endl;
//     }
//     A(A&& a)
//     {
//         this->data_ = a.data_;
//         a.data_     = nullptr;
//         std::cout << "move " << std::endl;
//     }
//     void print()
//     {
//         std::cout << "date = " << *data_ << std::endl;
//     }
//     ~A()
//     {
//         if (data_ != nullptr)
//         {
//             delete[] data_;
//         }
//         std::cout << "destruct1" << std::endl;
//     }
//     int* data_;
//     int  size_;
// };
// int main()
// {
//     A a(10);
//     A b = a;
//     A c = std::move(a);  // 调用移动构造函数
//     // 转移了所有权，
//     a.print();
//     return 0;
// }

// void PrintV(int &t)
// {
//     std::cout << "lvalue" << std::endl;
// }
// void PrintV(int &&t)
// {
//     std::cout << "rvalue" << std::endl;
// }
// template <typename T>
// void Test(T &&t)
// {
//     PrintV(t);
//     PrintV(std::forward<T>(t));
//     PrintV(std::move(t));
// }
// int main()
// {
//     Test(1);  // lvalue rvalue rvalue
//     int a = 1;
//     int &c = a;
//     Test(a);                        // lvalue lvalue rvalue
//     auto b = std::forward<int>(a);
//     std::cout << "a type: " << typeid(a).name() << std::endl;
//     std::cout << "b type: " << typeid(b).name() << std::endl;
//     Test(std::forward<int>(a));     // lvalue rvalue rvalue
//     Test(std::forward<int &>(a));   // lvalue lvalue rvalue
//     Test(std::forward<int &&>(a));  // lvalue rvalue rvalue
//     return 0;
// }

// 计时器
// #include <iostream>
// #include <chrono>
// #include <thread>

// int main() {
//     // 设置要运行的循环时间（以秒为单位）
//     int run_time_seconds = 5;  // 5秒

//     // 获取当前时间点
//     auto start_time = std::chrono::high_resolution_clock::now();

//     while (true) {
//         // 在此处执行循环的工作

//         // 获取当前时间点
//         auto current_time = std::chrono::high_resolution_clock::now();

//         // 计算经过的时间（以秒为单位）
//         std::chrono::duration<double> elapsed_seconds = current_time - start_time;

//         // 如果经过的时间超过了设定的运行时间，退出循环
//         if (elapsed_seconds.count() >= run_time_seconds) {
//             break;
//         }

//         // 可以添加适当的睡眠来降低循环执行速度，以减轻CPU负载
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     }

//     // 循环结束后执行其他操作
//     std::cout << "Loop has run for " << run_time_seconds << " seconds and is now stopping." << std::endl;

//     return 0;
// }

// template <typename R, typename U = int>
// R func1(U val)
// {
//     cout << "func1 val type = " << typeid(val).name() << " val = " << val << endl;
//     return val;
// }
// template <typename R = int, typename U>
// R func2(U val)
// {
//     cout << "func2 val type = " << typeid(val).name() << " val = " << val << endl;
//     return val;
// }

// template <typename R , typename U>
// R func3(U val)
// {
//     cout << "func2 val type = " << typeid(val).name() << " val = " << val << endl;
//     return val;
// }

// int main()
// {
//     cout << func1<int, double>(99.9) << endl;     // 99
//     cout << func1<double, double>(99.9) << endl;  // 99.9
//     cout << func1<double>(99.9) << endl;          // 99.9
//     cout << func1<int>(99.9) << endl;             // 99
//     cout << func2<int, double>(99.9) << endl;     // 99
//     cout << func1<double, double>(99.9) << endl;  // 99.9
//     cout << func2<double>(99.9) << endl;          // 99.9
//     cout << func2<int>(99.9) << endl;             // 99
//     auto i = func3<int>(99.9);
//     cout << "i type = " << typeid(i).name() << " i = " << i << endl;  // 99.9
//     return 0;
// }

#include<ratio>
#include<ctime>
#include<iomanip>
// int main()
// {
//     auto cur_time = std::chrono::high_resolution_clock::now();
//     auto timestamp = std::chrono::high_resolution_clock::to_time_t(cur_time);
//     std::chrono::seconds(1);
//     std::cout << "time = " << std::ctime(&timestamp) << std::endl;
//     std::chrono::milliseconds ms{3};
//     std::chrono::microseconds us{200};
//     std::cout << "ms:" << ms.count() << "us=" << us.count() << endl;
//     std::chrono::microseconds t = ms - us;
//     std::chrono::duration_cast<std::chrono::microseconds>(ms - us);
//     std::cout << "t = " << t.count() << endl;

//     typedef std::chrono::duration<int, std::ratio<60 * 60 * 24>> days_type;
//     std::chrono::time_point<std::chrono::system_clock, days_type> today =
//         std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());
//     std::time_t today_t = std::chrono::system_clock::to_time_t(today);
//     std::cout << "today = " << today.time_since_epoch().count() << " time = "<< std::put_time(std::localtime(&today_t), "%F %T")<< endl;
//     return 0;
// }


// class Timer
// {
// public:
//     Timer() : m_begin_(std::chrono::high_resolution_clock::now())
//     {
//         // auto timestamp = std::chrono::high_resolution_clock::to_time_t(m_begin_);
//         // std::cout << "time = " << std::ctime(&timestamp) << std::endl;
//     }
//     ~Timer(){}
//     void reset()
//     {
//         m_begin_ = std::chrono::high_resolution_clock::now();
//     }
//     template<typename Duration=std::chrono::milliseconds>
//     int elapsed() const
//     {
//         return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin_).count();
//     }

//     int64_t elapsed_micro()const
//     {
//         return elapsed<std::chrono::milliseconds>();
//     }

//     int64_t elapsed_nano()const
//     {
//         return elapsed<std::chrono::microseconds>();
//     }

// private:
//     std::chrono::time_point<std::chrono::high_resolution_clock> m_begin_;
// };

// void func()
// {
//     std::cout << "timer" << std::endl;
//     //std::this_thread::sleep_for(std::chrono::milliseconds(1));
// }

// int main()
// {
//     Timer t;
//     func();
//     std::cout << t.elapsed() << std::endl;
//     std::cout << t.elapsed_nano() << std::endl;
//     return 0;
// }


// int main()
// {
//     std::vector<int> v;
//     int              a = 10;
//     v.emplace_back(a);
//     for (auto i: v)
//     {
//         std::cout << "value = " << i << std::endl;
//     }
//     return 0;
// }

// class MyClass {
// public:
//     // 一个较为复杂的构造函数
//     MyClass(int value) : value_(value), data_(new int[10000]) {
//         // 模拟一些复杂的对象构造逻辑
//         for (int i = 0; i < 10000; ++i) {
//             data_[i] = i;
//         }
//     }

//     // 移动构造函数
//     MyClass(MyClass&& other) noexcept : value_(other.value_), data_(other.data_) {
//         other.data_ = nullptr;
//     }

//     ~MyClass() {
//         delete[] data_;
//     }

// private:
//     int value_;
//     int* data_;
// };

// int main() {
//     const int numElements = 100000;

//     // 使用 push_back
//     auto startPushBack = std::chrono::high_resolution_clock::now();
//     std::vector<MyClass> vectorPushBack;
//     for (int i = 0; i < numElements; ++i) {
//         vectorPushBack.push_back(MyClass(i));
//     }
//     auto endPushBack = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> durationPushBack = endPushBack - startPushBack;

//     // 使用 emplace_back
//     auto startEmplaceBack = std::chrono::high_resolution_clock::now();
//     std::vector<MyClass> vectorEmplaceBack;
//     for (int i = 0; i < numElements; ++i) {
//         vectorEmplaceBack.emplace_back(i);
//     }
//     auto endEmplaceBack = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> durationEmplaceBack = endEmplaceBack - startEmplaceBack;

//     std::cout << "push_back duration: " << durationPushBack.count() << " seconds\n";
//     std::cout << "emplace_back duration: " << durationEmplaceBack.count() << " seconds\n";

//     return 0;
// }

// class Foo
// {
// public:
//     int val;
//     Foo *pnext;

// };

// int main()
// {
//     Foo bar;
//     Foo bar2 = Foo();
//     if(bar.val)
//     {
//         cout << "val" << endl;
//     }
//     if(bar.pnext)
//     {
//         cout << "pnext" << endl;
//     }
//     return 0;
// }

// class Shape
// {
// public:
//     virtual void test() = 0;
//     int          test2();
// };

// int main()
// {
//     int arr[5] = {1, 2, 3, 4, 5};
//     cout << *(arr + 1) << endl;
//     cout << &arr << endl;
//     cout << &arr+1 << endl;
//     int* a = &arr[0];
//     int  b = 0;
//     cout << sizeof(a) << endl;
//     cout << sizeof(b) << endl;
//     char c[] = {'a','b','c'};
//     char d[] = {"abc"};
//     cout << sizeof(c) << endl;
//     cout << sizeof(d) << endl;
//     //Shape sp; 抽象类不允许实例化
//     return 0;
// }

// #include<cstring>
// struct Data
// {
//     int a;
//     char* c;
//     Data(int i, const char* c_):a(i)
//     {
//         c = new char[std::strlen(c) + 1];
//         std::strcpy(c, c_);
//     }
// };
// class A
// {
// public:
//     void foo(int& a)
//     {
//         cout << a << endl;
//     }
//     void foo(int&& a)
//     {
//         cout << "rValue reference "<< a << endl;
//     }
//     Data&& test()
//     {
//         Data b(1, "cas");
//         //return std::move(b);
//         return b;
//     }
// private:
//     int data;
// };

// int main()
// {
//     vector<int> arr;
//     A           a;
//     int         data = 1;
//     a.foo(data);
//     a.foo(std::move(data));
//     //Data c = a.test();
//     cout << a.test().a << endl;
//     return 0;
// }

// void noexceptFunction() noexcept {
//     //throw std::runtime_error("This is an exception inside a noexcept function.");
//     int arr[5] = {1, 2, 3, 4, 5};

//     // 访问越界数组元素
//     std::cout << arr[11] << std::endl;
// }

// int main() {
//     try {
//         noexceptFunction();
//     } catch (const std::exception& e) {
//         std::cerr << "Caught exception: " << e.what() << std::endl;
//     }

//     return 0;
// }

// template <typename T>

// // 基本情况的模板函数
// void print(const T& arg) {
//     std::cout << std::endl;
// }

// // 可变参数模板的递归函数
// template <typename T, typename... Args>
// void print(T first, Args... args) {
//     std::cout << first << " ";
//     print(args...);
// }

// int main() {
//     print(1, 2.5, "Hello", 'a');
//     return 0;
// }

// 在c++中可以不写return 0, 不同于C，C++会默认补上return 0
int main()
{
    cout << "test" << endl;
    exit(0);
}
