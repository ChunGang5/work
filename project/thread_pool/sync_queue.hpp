/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-09-06 17:30:43
 */

#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
#include <thread>

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
        add(std::forward<T>(x));
    }

private:
    bool notFull()const
    {
        bool full = m_queue.size() >= m_maxSize;
        if(full)
        {
            std::cout << "缓冲区满了, 需等待....., 异步层的线程ID: " << std::this_thread::get_id() << std::endl;
        }
        return !full;
    }

    template<typename F>
    void add(F&&x)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notFull.wait(locker, [this] { return m_needStop || notFull(); });
        if (m_needStop)
        {
            return;
        }
        m_queue.push_back(std::forward<F>(x));
        m_notFull.notify_one();
    }

private:
    std::list<T> m_queue;
    std::mutex   m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
    int                     m_maxSize;
    bool m_needStop;
};
