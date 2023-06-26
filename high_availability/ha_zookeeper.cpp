/**
 * @file ha_zookeeper.cpp
 * @brief To-be-added
 * @copyright Copyright (c) 2020 YUSUR Technology Co., Ltd. All Rights Reserved. Learn more at www.yusur.tech.
 * @author Chen Gang (cheng_caft@yusur.tech)
 * @date 2023-06-26 11:22:32
 * @last_author:
 * @last_edit_time:
 */
#include "ha_zookeeper.h"
#include "ha_role_state_manager.h"
#include "rcm/rcm.h"

#include "logger/spd_logger_manager.h"
#include "conf_manager/conf_manager.h"
#include "base/macros.h"
#include "conf_manager/ha_zookeeper_conf.h"
#include "base/time_util.h"
#include <unistd.h>

HAZookeeper::HAZookeeper() {}

HAZookeeper::~HAZookeeper() {}

bool HAZookeeper::init()
{
    host_list_                   = GET_CONF(HAZookeeperConf)->zk_addr;
    zk_root_node_path_           = GET_CONF(HAZookeeperConf)->zk_root_node_path;
    server_name_                 = GET_CONF(HAZookeeperConf)->server_name;
    recv_timeout_                = GET_CONF(HAZookeeperConf)->recv_timeout_;
    max_connect_times            = GET_CONF(HAZookeeperConf)->max_connect_times;
    max_zk_server_timeout_times_ = GET_CONF(HAZookeeperConf)->max_zk_server_timeout_times;
    check_zk_server_interval_    = GET_CONF(HAZookeeperConf)->check_zk_server_interval;
    is_running_.store(true);
    p_check_zookeeper_server_ = nullptr;
    return true;
}

void HAZookeeper::close()
{
    if (zk_handle_)
    {
        zookeeper_close(zk_handle_);
    }
    zk_handle_ = nullptr;
}

void HAZookeeper::shutdown()
{
    is_running_.store(false);
    if (p_check_zookeeper_server_ && p_check_zookeeper_server_->joinable())
    {
        p_check_zookeeper_server_->join();
        delete p_check_zookeeper_server_;
        p_check_zookeeper_server_ = nullptr;
    }
    close();
}

void string_completion(int rc, const char* name, const void* data)
{
    LOG_INFO("<High_Availability> {0}: rc= {1}", (char*)(data == 0 ? "null" : data), rc);
    if (rc != ZOK)
    {
        LOG_ERROR("<High_Availability> name = {0}, rc = {1}", name, rc);
    }
}

void stat_completion(int rc, const struct Stat* stat, const void* data)
{
    LOG_INFO("<High_Availability> Zoo_awexists complete!");
}

bool HAZookeeper::connect()
{
    if (zk_handle_)
    {
        zookeeper_close(zk_handle_);
        zk_handle_ = nullptr;
    }
    int count = 0;
    while (count < max_connect_times)
    {
        ++count;
        zk_handle_ = zookeeper_init(host_list_.c_str(), nullptr, recv_timeout_, 0, NULL, 0);
        if (zk_handle_ != NULL)
        {
            int state = zoo_state(zk_handle_);
            if (state == ZOO_CONNECTED_STATE)
            {
                LOG_INFO("<High_Availability> Zookeeper connect success, host list = {}", host_list_);
                return true;
            }
        }
    }
    LOG_ERROR(
        "<High_Availability> Failed to connect to Zookeeper host {0} after {1} attempts.",
        host_list_,
        max_connect_times);
    return false;
}

void children_watcher(zhandle_t* zh, int type, int state, const char* path, void* watcherCtx)
{
    if (state == ZOO_CONNECTED_STATE)
    {
        if (type == ZOO_CHILD_EVENT)
        {
            std::string root_node_path   = yusur::Singleton<HAZookeeper>().get_instance().get_zk_root_node();
            std::string leader_lock_path = root_node_path + "/Leader" + "/Lock";
            // 重新获取子节点列表
            struct String_vector children;
            memset(&children, 0, sizeof(children));
            int rc = zoo_get_children(zh, path, 1, &children);
            if (rc == ZOK)
            {
                for (int i = 0; i < children.count; ++i)
                {
                    LOG_INFO("Children: {}", children.data[i]);
                }
                if (children.count == 1)
                {
                    LOG_INFO("<HighAvailability> 单机，无备机, nRole = {0}", rcm::RCM_ROLE_SINGLE);
                    RoleStateManager::get_instance().set_cur_role_state(RoleState::ROLE_SINGLE);

                    int rc = zoo_create(
                        yusur::Singleton<HAZookeeper>().get_instance().get_zk_handle(),
                        leader_lock_path.c_str(),
                        yusur::Singleton<HAZookeeper>().get_instance().get_server_name().c_str(),
                        yusur::Singleton<HAZookeeper>().get_instance().get_server_name().size(),
                        &ZOO_OPEN_ACL_UNSAFE,
                        ZOO_EPHEMERAL,
                        nullptr,
                        0);
                    if (rc == ZNODEEXISTS)
                    {
                        int ret = zoo_set(
                            yusur::Singleton<HAZookeeper>().get_instance().get_zk_handle(),
                            leader_lock_path.c_str(),
                            yusur::Singleton<HAZookeeper>().get_instance().get_server_name().c_str(),
                            yusur::Singleton<HAZookeeper>().get_instance().get_server_name().size(),
                            -1);
                        if (ret != ZOK)
                        {
                            LOG_ERROR("<High_Availability> Leader lock node set data error, ret = {}", ret);
                        }
                    }
                    else if (rc != ZOK)
                    {
                        LOG_ERROR("<High_Availability> Create leader lock node fail, rc = {0}", rc);
                    }
                }
                else if (children.count == 2)
                {
                    char buffer[1024];
                    int  buffer_len = sizeof(buffer);
                    rc              = zoo_get(
                        yusur::Singleton<HAZookeeper>().get_instance().get_zk_handle(),
                        leader_lock_path.c_str(),
                        0,
                        buffer,
                        &buffer_len,
                        nullptr);
                    if (rc == ZOK)
                    {
                        std::string leader_lock_data = std::string(buffer, buffer_len);
                        LOG_INFO("<High_Availability> Leader_lock_data = {}", leader_lock_data);

                        if (leader_lock_data.compare(
                                yusur::Singleton<HAZookeeper>().get_instance().get_server_name()) == 0)
                        {
                            // 转主节点运行状态
                            RoleStateManager::get_instance().set_cur_role_state(RoleState::ROLE_MASTER);
                            LOG_INFO("<HighAvailability> 主机，有备机, nRole = {0}", rcm::RCM_ROLE_ACTIVE);
                        }
                        else
                        {
                            RoleStateManager::get_instance().set_cur_role_state(RoleState::ROLE_SLAVE);  // 备机
                            LOG_INFO("<HighAvailability> 备机, nRole = {0}", rcm::RCM_ROLE_INACTIVE);
                        }
                    }
                    else
                    {
                        LOG_ERROR("<High_Availability> Get node data error, rc = {}", rc);
                    }
                }
                else
                {
                    LOG_WARN("<High_Availability> Only two nodes are supported!");
                }
                // 释放子节点列表的内存
                deallocate_String_vector(&children);
            }
            else
            {
                LOG_ERROR("<High_Availability> Failed to get children of {}", path);
            }

            int ret = zoo_wget_children(
                yusur::Singleton<HAZookeeper>().get_instance().get_zk_handle(),
                yusur::Singleton<HAZookeeper>().get_instance().get_cluster_path().c_str(),
                children_watcher,
                NULL,
                &children);
            if (ret != ZOK)
            {
                LOG_ERROR("<High_Availability> Wget childern node error, rc = {}", ret);
            }
            // 释放子节点列表的内存
            deallocate_String_vector(&children);
        }
    }
}

#define YUSUR_ZOO_EXPIRED_SESSION_STATE 0  // -112

void HAZookeeper::check_zookeeper_server()
{
    LOG_INFO("<High_Availability> Check_zookeeper_server runnning");
    int timeout_count = 0;
    while (is_running_.load())
    {
        int state = zoo_state(zk_handle_);
        if (state == YUSUR_ZOO_EXPIRED_SESSION_STATE)
        {
            LOG_ERROR("<High_Availability> State = {}, ZOO_EXPIRED_SESSION_STATE, zookeeper server death", state);
            if (timeout_count < max_zk_server_timeout_times_)
            {
                LOG_ERROR("<High_Availability> Timeout_count = {}", timeout_count);
                ++timeout_count;
                continue;
            }
            is_running_.store(false);
            if (RoleStateManager::get_instance().get_cur_role_state() == RoleState::ROLE_MASTER)
            {
                RoleStateManager::get_instance().set_cur_role_state(RoleState::ROLE_SINGLE);
            }
            else if (RoleStateManager::get_instance().get_cur_role_state() == RoleState::ROLE_SLAVE)
            {
                RoleStateManager::get_instance().set_cur_role_state(RoleState::ROLE_DEAD);
            }
            close();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(check_zk_server_interval_));
        timeout_count = 0;
    }
}

bool HAZookeeper::start()
{
    zoo_set_debug_level(ZOO_LOG_LEVEL_ERROR);

    if (!connect())
    {
        return false;
    }

    // 监测zookeeper服务器的状态
    p_check_zookeeper_server_ = new std::thread(&HAZookeeper::check_zookeeper_server, this);

    if (!create_node(zk_root_node_path_, "", 0))
    {
        LOG_WARN("<High_Availability> Create root node fail");
    }

    cluster_path_ = zk_root_node_path_ + "/Cluster";
    if (!create_node(cluster_path_, "", 0))
    {
        LOG_WARN("<High_Availability> Create cluster node fail");
    }

    std::string leader_path = zk_root_node_path_ + "/Leader";
    if (!create_node(leader_path, "", 0))
    {
        LOG_WARN("<High_Availability> Create leader node fail");
    }

    // 注册子节点变化的Watcher
    struct String_vector children;
    memset(&children, 0, sizeof(children));
    int rc = zoo_wget_children(zk_handle_, cluster_path_.c_str(), children_watcher, NULL, &children);
    if (rc != ZOK)
    {
        LOG_ERROR("<High_Availability> Failed to register children watcher for {}", cluster_path_);
        return -1;
    }

    const std::string server_node = cluster_path_ + "/" + server_name_;  // server1
    init_create_node(server_node, server_name_, ZOO_EPHEMERAL, (void*)"acreate node");

    // 获取子节点列表并打印
    rc = zoo_get_children(zk_handle_, cluster_path_.c_str(), 1, &children);
    if (rc == ZOK)
    {
        for (int i = 0; i < children.count; ++i)
        {
            LOG_INFO("<High_Availability> Child = {}", children.data[i]);
        }
    }
    else
    {
        LOG_ERROR("<High_Availability> Get childer error, ret = {}", rc);
    }

    LOG_INFO("<High_Availability> Watch node success");
    return true;
}

bool HAZookeeper::init_create_node(const std::string& node_path, const std::string& value, int flags, void* context)
{
    bool flag = create_node_async(node_path, value, flags, context, string_completion);

    if (flag)
    {
        LOG_INFO("<High_Availability> Created node {0}.", node_path);
        return true;
    }
    else
    {
        LOG_ERROR("<High_Availability> Failed to create node {0}.", node_path);
        return false;
    }
}

bool HAZookeeper::create_node(const std::string& path, const std::string& value, const int flags)
{
    int ret =
        zoo_create(zk_handle_, path.c_str(), value.c_str(), value.size(), &ZOO_OPEN_ACL_UNSAFE, flags, nullptr, 0);
    if (ret == ZNODEEXISTS)
    {
        LOG_WARN("<High_Availability> The node already exists.");
        return true;
    }
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}

bool HAZookeeper::create_node_async(
    const std::string&  path,
    const std::string&  value,
    int                 flags,
    void*               context,
    string_completion_t completion)
{
    int ret = zoo_acreate(
        zk_handle_, path.c_str(), value.c_str(), value.length(), &ZOO_OPEN_ACL_UNSAFE, flags, completion, context);
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}

bool HAZookeeper::delete_node(const std::string& path, int version)
{
    int ret = zoo_delete(zk_handle_, path.c_str(), version);
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}

bool HAZookeeper::delete_node_async(const std::string& path, int version, void* context, void_completion_t completion)
{
    int ret = zoo_adelete(zk_handle_, path.c_str(), version, completion, context);
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}

std::string HAZookeeper::get_node_data(const std::string& path)
{
    char buffer[1024];
    int  buffer_len = sizeof(buffer);
    int  ret        = zoo_get(zk_handle_, path.c_str(), 0, buffer, &buffer_len, nullptr);
    if (ret == ZOK)
    {
        return std::string(buffer, buffer_len);
    }
    return "";
}

bool HAZookeeper::get_node_data_async(const std::string& path, void* context, data_completion_t completion)
{
    int ret = zoo_aget(zk_handle_, path.c_str(), 0, completion, context);
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}

bool HAZookeeper::set_node_data(const std::string& path, const std::string& value, int version = -1)
{
    int ret = zoo_set(zk_handle_, path.c_str(), value.c_str(), value.length(), version);
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}

bool HAZookeeper::set_node_data_async(
    const std::string& path,
    const std::string& value,
    int                version,
    void*              context,
    stat_completion_t  completion)
{
    int ret = zoo_aset(zk_handle_, path.c_str(), value.c_str(), value.length(), version, completion, context);
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}

bool HAZookeeper::exists(const std::string& path)
{
    struct Stat stat;
    int         ret = zoo_exists(zk_handle_, path.c_str(), 0, &stat);
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}

bool HAZookeeper::exists_async(const std::string& path, void* context, stat_completion_t completion)
{
    int ret = zoo_aexists(zk_handle_, path.c_str(), 0, completion, context);
    if (ret == ZOK)
    {
        return true;
    }
    return false;
}
