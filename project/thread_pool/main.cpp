/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-09-06 17:11:27
 */

#include "thread_pool.hpp"

void test()
{
    ThreadPool pool;
    pool.Start(2);

    std::thread thd1(
        [&pool]
        {
            for (int i = 0; i < 10; i++)
            {
                auto thId = std::this_thread::get_id();
                pool.addTask([thId] { std::cout << "同步线程1的线程id为：" << thId << std::endl; });
            }
        });

    std::thread thd2(
        [&pool]
        {
            for (int i = 0; i < 10; i++)
            {
                auto thId = std::this_thread::get_id();
                pool.addTask([thId] { std::cout << "同步线程2的线程id为：" << thId << std::endl; });
            }
        });

    std::this_thread::sleep_for(std::chrono::seconds(2));
    getchar();
    pool.stop();
    thd1.join();
    thd2.join();
}

int main()
{
    test();
    return 0;
}
