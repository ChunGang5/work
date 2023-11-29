/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-11-28 17:40:05
 */

#include <atomic>
#include <functional>
#include <memory>
#include <thread>

#include "sync_queue.hpp"

const int MaxTaskCount = 100;
class ThreadPool
{
public:
    using Task = std::function<void()>;

    ThreadPool(int numThreads = std::thread::hardware_concurrency()) : m_queue(MaxTaskCount) {}

    ~ThreadPool(){}

    void stop()
    {
        std::call_once(m_flag, [this] { stopThreadGroup(); });
    }

    void addTask(Task&&task)
    {
        m_queue.put(std::forward<Task>(task));
    }

    void addTask(const Task& task)
    {
        m_queue.put(task);
    }

    void Start(int numThreads)
    {
        m_running.store(true);
        // 创建线程组
        for (int i = 0; i < numThreads; i++)
        {
            m_threadGroup.emplace_back(std::make_shared<std::thread>(&ThreadPool::runInThread, this));
        }
    }
private:
    void runInThread()
    {
        while (m_running)
        {
            std::list<Task> list;
            m_queue.take(list);

            for (auto& task : list)
            {
                if (!m_running)
                {
                    return;
                }
                task();
            }
        }
    }

    void stopThreadGroup()
    {
        m_queue.stop();
        m_running.store(false);

        for (auto& thread : m_threadGroup)
        {
            if (thread && thread->joinable())
            {
                thread->join();
            }
        }
        m_threadGroup.clear();
    }

    std::list<std::shared_ptr<std::thread>> m_threadGroup;
    SyncQueue<Task>                         m_queue;
    std::atomic_bool                        m_running;
    std::once_flag                          m_flag;
};
