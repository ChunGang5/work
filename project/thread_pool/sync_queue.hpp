/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-09-06 17:30:43
 */
class SyncQueue
{
public:
    SyncQueue(int maxSize): m_maxSize(maxSize), m_needStop(false)
    {
    }
    ~SyncQueue()
    {}

private:
    int m_maxSize;
    bool m_needStop;
};
