/**
 * @file ha_role_state_manager.cpp
 * @brief To-be-added
 * @copyright Copyright (c) 2020 YUSUR Technology Co., Ltd. All Rights Reserved. Learn more at www.yusur.tech.
 * @author Chen Gang (cheng_caft@yusur.tech)
 * @date 2023-04-10 15:25:24
 */

#include "ha_role_state_manager.h"

const char* role_state_to_string(const RoleState role_state)
{
    switch (role_state)
    {
    case ROLE_INIT:
        return "ROLE_INIT";
    case ROLE_SINGLE:
        return "ROLE_SINGLE";
    case ROLE_SINGLE_ZK_OFFLINE:
        return "ROLE_SINGLE_ZK_OFFLINE";
    case ROLE_MASTER:
        return "ROLE_MASTER";
    case ROLE_SLAVE:
        return "ROLE_SLAVE";
    case ROLE_DEAD:
        return "ROLE_DEAD";
    default:
        return "ROLE_UNKNOWN";
    }
}

RoleStateManager::RoleStateManager() {}

RoleStateManager::~RoleStateManager()
{}

void RoleStateManager::set_cur_role_state(RoleState state)
{
    cur_role_state_code_ = state;
    notify();
}

RoleState RoleStateManager::get_cur_role_state()
{
    return cur_role_state_code_;
}

void RoleStateManager::notify()
{
    for (auto& observer : observers_)
    {
        observer(cur_role_state_code_);
    }
}
