/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-08-24 16:05:58
 */

// 单例
class Singleton
{
private:
    Singleton()
    {
        
    }
    static Singleton instance_;
public:
    Singleton &get_instance()
    {
        return instance_;
    }
};
