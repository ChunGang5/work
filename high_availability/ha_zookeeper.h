/**
 * @file ha_zookeeper.h
 * @brief To-be-added
 * @copyright Copyright (c) 2020 YUSUR Technology Co., Ltd. All Rights Reserved. Learn more at www.yusur.tech.
 * @author Chen Gang (cheng_caft@yusur.tech)
 * @date 2023-06-26 11:21:58
 * @last_author:
 * @last_edit_time:
 */
#ifndef _HIGH_AVAILABILITY_HA_ZOOKEEPER_H_
#define _HIGH_AVAILABILITY_HA_ZOOKEEPER_H_


#include "zookeeper/zookeeper.h"


#include <string>
#include <thread>
#include <atomic>
#include <chrono>

// 定义内部服务故障枚举
enum InternalServiceFailure
{
    FPGA_HEARTBEAT_TIMEOUT = 1,
    RC_MASTER_SLAVE_HEARTBEAT_TIMEOUT
};

// TODO:改为单例类
class HAZookeeper
{
public:
    HAZookeeper();

    virtual ~HAZookeeper();

    /**
     * @brief 初始化
     *
     * @return true
     * @return false
     */
    bool init();

    /**
     * @brief client端连接zookeeper server
     *
     * @return true
     * @return false
     */
    bool connect();

    /**
     * @brief 启动zk模块
     *
     */
    bool start();

    /**
     * @brief 关闭zk的客户端
     *
     */
    void close();

    /**
     * @brief 关闭高可用模块的zk
     *
     */
    void shutdown();

    /**
     * @brief 以同步的方式创建一个节点
     *
     * @param path  要创建的节点的路径
     * @param value 节点值
     * @param flags 创建节点的类型，该参数可以设置为 0，或者创建标识符 ZOO_EPHEMERAL(临时), ZOO_SEQUENCE(顺序节点)
     * 的组合或(OR)。
     */
    bool create_node(const std::string& path, const std::string& value, const int flags);

    /**
     * @brief 异步方式创建节点
     *
     * @param path  要创建的节点的路径
     * @param value 节点值
     * @param flags 创建节点的类型，该参数可以设置为 0，或者创建标识符 ZOO_EPHEMERAL(临时), ZOO_SEQUENCE(顺序节点)
     * 的组合或(OR)。
     * @param context 上下文，传入回调函数内
     * @param completion 回调函数
     * @return true
     * @return false
     */
    bool create_node_async(
        const std::string&  path,
        const std::string&  value,
        int                 flags,
        void*               context,
        string_completion_t completion);

    /**
     * @brief 删除节点
     *
     * @param path 要删除的节点路径
     * @param version 版本，-1为不检查
     * @return true
     * @return false
     */
    bool delete_node(const std::string& path, int version);

    /**
     * @brief 异步方式删除节点
     *
     * @param path 要删除的节点路径
     * @param version 版本，-1为不检查
     * @param context 上下文，传入回调函数内
     * @param completion 回调函数
     * @return true
     * @return false
     */
    bool delete_node_async(const std::string& path, int version, void* context, void_completion_t completion);

    /**
     * @brief 获取节点值
     *
     * @param path 节点路径
     * @return std::string 获取到的值
     */
    std::string get_node_data(const std::string& path);

    /**
     * @brief 异步方式获取节点值
     *
     * @param path 节点路径
     * @param context 上下文，传入回调函数内
     * @param completion 回调函数
     * @return true
     * @return false
     */
    bool get_node_data_async(const std::string& path, void* context, data_completion_t completion);

    /**
     * @brief 设置节点值
     *
     * @param path 节点路径
     * @param value 节点值
     * @param version 版本，-1为不检查
     * @return true
     * @return false
     */
    bool set_node_data(const std::string& path, const std::string& value, int version);

    /**
     * @brief 异步方式设置节点值
     *
     * @param path 节点路径
     * @param value 节点值
     * @param version 版本，-1为不检查
     * @param context 上下文
     * @param completion 回调函数
     * @return true
     * @return false
     */
    bool set_node_data_async(
        const std::string& path,
        const std::string& value,
        int                version,
        void*              context,
        stat_completion_t  completion);

    /**
     * @brief 判断节点是否存在
     *
     * @param path 节点路径
     * @return true
     * @return false
     */
    bool exists(const std::string& path);

    /**
     * @brief 异步方式判断节点是否存在
     *
     * @param path 节点路径
     * @param context 上下文
     * @param completion 回调函数
     * @return true
     * @return false
     */
    bool exists_async(const std::string& path, void* context, stat_completion_t completion);

    /**
     * @brief 初始化异步方式创建节点
     *
     * @param node_path 节点路径
     * @param value 节点值
     * @param flags 节点类型
     * @param context 上下文
     * @return true
     * @return false
     */
    bool init_create_node(const std::string& node_path, const std::string& value, int flags, void* context);

    /**
     * @brief 获取zk客户端句柄
     *
     * @return zhandle_t*
     */
    inline zhandle_t* get_zk_handle()
    {
        return zk_handle_;
    }

    /**
     * @brief 获取zk根节点路径
     *
     * @return std::string
     */
    inline std::string get_zk_root_node()
    {
        return zk_root_node_path_;
    }

    /**
     * @brief 获取高可用服务节点名称
     *
     * @return std::string
     */
    inline std::string get_server_name()
    {
        return server_name_;
    }

    /**
     * @brief 获取节点集群路径
     *
     * @return std::string
     */
    inline std::string get_cluster_path()
    {
        return cluster_path_;
    }

    /**
     * @brief 检测zk服务端的状态
     *
     */
    void check_zookeeper_server();

private:
    // 处理返回 void 类型的回调函数
    typedef void (*void_completion_t)(int rc, const void* data);

    // 返回 Stat 结构的回调函数
    typedef void (*stat_completion_t)(int rc, const struct Stat* stat, const void* data);

    // 返回字符串的回调函数
    typedef void (*string_completion_t)(int rc, const char* value, const void* data);

    // 返回数据的回调函数
    typedef void (
        *data_completion_t)(int rc, const char* value, int value_len, const struct Stat* stat, const void* data);

    std::string      host_list_;         // 要连接的zk服务地址
    zhandle_t*       zk_handle_ = NULL;
    std::uint32_t    max_connect_times;  // 最大连接次数
    std::uint32_t    recv_timeout_;      // 客户端接收超时时间
    std::string      node_path_;
    std::string      zk_root_node_path_;
    std::string      server_name_;  // 高可用服务节点名称
    std::string      cluster_path_;
    std::thread*     p_check_zookeeper_server_;
    std::atomic_bool is_running_;
    std::uint32_t    max_zk_server_timeout_times_;
    std::uint32_t    check_zk_server_interval_;
};

#endif  //_HIGH_AVAILABILITY_HA_ZOOKEEPER_H_
