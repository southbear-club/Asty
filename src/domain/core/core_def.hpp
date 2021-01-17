/**
 * @file core_def.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <functional>
#include "../../common/dev_sdk_errno.hpp"
#include "../../common/datatype.hpp"
#include "../../net/net_def.hpp"

namespace asty_gw_sdk
{

typedef struct domain_core_init_s domain_core_init_t;
typedef struct domain_core_callback_s domain_core_callback_t;

/**
 * @brief 核心领域错误码
 * 
 */
typedef enum {
    sdk_core_err_ok = sdk_err_ok,
    sdk_core_err_unknown = sdk_err_core + 0x1,
} domain_core_errno_t;

/**
 * @brief 设备网关网络
 * 
 */
struct dev_gw_net_conf {
    std::string interface;
};

/**
 * @brief 核心领域回调接口
 * 
 */
struct domain_core_callback_s {
    std::function<domain_core_errno_t(sdk_msg_t&)> device_identi;    ///< 设备注册返回识别码，设备上线查询识别码
    std::function<domain_core_errno_t(sdk_msg_t&)> master_key;       ///< 通信密钥，用于生成session
    std::function<domain_core_errno_t(sdk_msg_t&)> event_notice;     ///< 核心领域事件通知
};

/**
 * @brief sdk初始化参数
 * 
 */
struct domain_core_init_s {
    struct netif_host platform_host;             ///< 平台地址
    struct dev_gw_net_conf local_net;   ///< 本地网络配置
    std::string device_info;            ///< 设备信息
    domain_core_callback_t cb;                  ///< 核心领域事件通知
};

/**
 * device type 设备型号
 * device serial 设备序列号，用来报备的
 * mac 设备mac地址
 * Verification code 验证码，用于设备注册的，报备后平台分配的那个
 * name 设备名称
 * nikname 别名
 * firmware code 固件代码
 */

} // namespace asty_gw_sdk
