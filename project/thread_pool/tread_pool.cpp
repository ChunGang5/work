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
    bool run() {}

    bool stop()
    {

    }
private:
    std::list<std::shared_ptr<std::thread>> m_threadGroup;
    SyncQueue<Task>                         m_queue;
    std::atomic_bool m_running;
    std::once_flag   m_flag;
};
