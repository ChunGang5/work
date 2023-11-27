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

    void take(std::list<T>& list)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] { return m_needStop || notEmpty(); });
        if(m_needStop)
        {
            return;
        }
        list = std::move(m_queue);
        m_notEmpty.notify_one();
    }

    void task(T& t)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] { return m_needStop || notEmpty(); });
        t = m_queue.front();
        m_queue.pop_front();
        m_notEmpty.notify_one();
    }

    void stop()
    {
        {
            std::unique_lock<std::mutex> locker(m_mutex);
            m_needStop = true;
        }
        m_notEmpty.notify_all();
        m_notFull.notify_all();
    }

    bool empty()
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    bool full()
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        return m_queue.size() == m_maxSize;
    }

    int count()
    {
        return m_queue.size();
    }

    size_t size()
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        return m_queue.size();
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

    bool notEmpty() const
    {
        bool empty = m_queue.empty();
        if(empty)
        {
            std::cout << "队列空了，需要等待..., 异步层的线程id: " << std::this_thread::get_id() << std::endl;
        }
        return !empty;
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
