/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-06-26 11:22:52
 */
/**
 * @file ha_role_state_manager.h
 * @brief To-be-added
 * @copyright Copyright (c) 2020 YUSUR Technology Co., Ltd. All Rights Reserved. Learn more at www.yusur.tech.
 * @author Chen Gang (cheng_caft@yusur.tech)
 * @date 2023-04-10 15:15:08
 */
#pragma once

#include <functional>
#include <vector>

#include "base/noncopyable.h"

enum RoleState
{
    ROLE_INIT = 0,           // 系统初始状态
    ROLE_SINGLE,             // 单机运行（高可用架构下会在初始化过程中短暂出现）
    ROLE_SINGLE_ZK_OFFLINE,  // RCM接入失败，zk断连情况下的单机运行状态
    ROLE_MASTER,             // 主机
    ROLE_SLAVE,              // 备机
    ROLE_DEAD                // 将节点挂掉
};

/**
 * @brief RoleState转换为字符串
 *
 * @param role_state   角色状态
 * @return const char* 字符串
 */
const char* role_state_to_string(RoleState role_state);

class RoleStateManager : NonCopyable
{
public:
    /**
     * @brief 获取单例对象
     *
     * @return RoleStateManager&
     */
    static RoleStateManager& get_instance()
    {
        static RoleStateManager instance;
        return instance;
    }

    RoleStateManager();

    virtual ~RoleStateManager();

    /**
     * @brief 设置当前的角色状态
     *
     * @param new_role_state
     */
    void set_cur_role_state(RoleState new_role_state);

    /**
     * @brief 获取当前角色状态
     *
     * @return RoleState&
     */
    RoleState get_cur_role_state();

    /**
     * @brief 通知所有观察者
     *
     */
    void notify();

    /**
     * @brief 添加一个观察者
     *
     * @param observer
     */
    inline void add_observer(std::function<void(const RoleState&)> observer)
    {
        observers_.emplace_back(observer);
    }

private:
    RoleState                                   cur_role_state_code_;  // 当前系统状态
    std::vector<std::function<void(RoleState)>> observers_;            // 观察者列表
};
