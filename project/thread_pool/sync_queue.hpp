/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-09-06 17:30:43
 */

#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
using namespace std;

template <typename T>
class SyncQueue
{
public:
    SyncQueue(int maxSize): m_maxSize(maxSize), m_needStop(false)
    {
    }
    ~SyncQueue()
    {}

    void put(const T& x)
    {
        add(x);
    }

    void put(T&& x)
    {
        add(std::forward<T> x);
    }

private:
    template<typename F>
    void add(F&&x)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
    }

private:
    std::list<T> m_queue;
    std::mutex   m_mutex;
    int              m_maxSize;
    bool m_needStop;
};
