/**
 * @file user_info.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>
#include <stdint.h>

namespace asty {

namespace basic
{

typedef struct {
    std::string name;       ///< 用户名
    int permission;         ///< 用户权限
    std::string phone;      ///< 联系电话，只能绑定一个用户
    std::string email;      ///< 邮箱，只能绑定一个用户
    uint8_t sex;            ///< 性别
    uint32_t age;           ///< 年龄
    std::string addr;       ///< 联系地址
    std::string birthday;   ///< 创建时间
    std::string icon;       ///< 头像
    std::string desc;       ///< 个人简介
    uint8_t status;         ///< 用户状态
} user_base_info_t;

// TODO:增值服务：存储，消息推送，预览时常
// TODO:appkey，用户开放API app接入
    
} // namespace basic

}