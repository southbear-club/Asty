/**
 * @file domain_type.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

namespace asty_gw_sdk
{

typedef enum {
    E_ASTY_GW_DOMAIN_CORE = 0,          ///< 核心领域，负责网关注册，上线，消息分发
    E_ASTY_GW_DOMAIN_BASIC = 1,         ///< 基础领域，网关基本功能，基本信息, 用户绑定等
    E_ASTY_GW_DOMAIN_ALARM = 2,         ///< 告警领域，网关告警推送
    E_ASTY_GW_DOMAIN_DEVICE = 3,        ///< 设备领域，用于控制网关内的各种设备
    E_ASTY_GW_DOMAIN_MEDIA = 4,         ///< 媒体领域，媒体信息，如视频，图片，音频等
    E_ASTY_GW_DOMAIN_SPEC = 5,          ///< 特殊领域，一些开放性，实现性，扩展性功能
    E_ASTY_GW_DOMAIN_TRANSPORT = 6,     ///< 透传领域，消息透传
} AstyGwDomainType;

} // namespace asty_gw_sdk
