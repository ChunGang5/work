/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-06-09 10:57:09
 */

// /*数据竞争的问题*/
// #include <iostream>
// #include <thread>

// int counter = 0;

// void incrementCounter() {
//     for (int i = 0; i < 1000; ++i) {
//         counter++;
//     }
// }

// int main() {
//     std::thread t1(incrementCounter);
//     std::thread t2(incrementCounter);

//     t1.join();
//     t2.join();

//     std::cout << "Counter value: " << counter << std::endl;

//     return 0;
// }

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::vector<int> data; // 共享数据
std::mutex mtx;       // 互斥锁

void processData(int threadId)
{
    for (int i = 0; i < 100; ++i)
    {
        std::lock_guard<std::mutex> lock(mtx);
        // 在临界区内对共享数据进行操作
        data.push_back(i);
        std::cout << "Thread " << threadId << " added " << i << std::endl;
    }
}

int main()
{
    std::vector<std::thread> threads;

    for (int i = 0; i < 4; ++i)
    {
        threads.emplace_back(processData, i);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}
