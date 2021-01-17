/**
 * @file basic.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <stddef.h>
#include "../../common/dev_sdk_errno.hpp"
#include "../../common/datatype.hpp"
#include "../../net/net_def.hpp"
#include "../domain.hpp"

namespace asty_gw_sdk
{

typedef struct domain_basic_param_s domain_basic_param_t;
typedef struct sdk_basic_msg_s sdk_basic_msg_t;
typedef struct sdk_basic_msg_online_s sdk_basic_msg_online_t;
typedef struct sdk_basic_msg_offline_s sdk_basic_msg_offline_t;
typedef struct sdk_basic_msg_user_verify_s sdk_basic_msg_user_verify_t;
typedef struct sdk_basic_msg_bind_s sdk_basic_msg_bind_t;
typedef struct sdk_basic_msg_unbind_s sdk_basic_msg_unbind_t;
typedef struct sdk_basic_msg_delete_s sdk_basic_msg_delete_t;
typedef struct sdk_basic_msg_reginfo_s sdk_basic_msg_reginfo_t;

/**
 * @brief basic领域错误码
 * 
 */
typedef enum {
    sdk_basic_err_ok = sdk_err_ok,
} sdk_basic_errno_t;

/**
 * @brief 平台请求类型
 * 
 */
typedef enum {
    e_sdk_basic_req_user_verify = 0,
} sdk_basic_req_type;

/**
 * @brief 平台响应类型
 * 
 */
typedef enum {
    e_sdk_basic_res_online = 0,
    e_sdk_basic_res_offline = 1,
    e_sdk_basic_res_bind = 2,
    e_sdk_basic_res_unbind = 3,
} sdk_basic_res_type;

/**
 * @brief 设备数据类型
 * 
 */
typedef enum {
    e_sdk_basic_send_del = 0,
} sdk_basic_send_type;

/**
 * @brief sdk回调类型
 * 
 */
typedef enum {
    e_sdk_basic_sdk_reginfo = 0,
} sdk_basic_sdk_type;

/**
 * @brief 用户验证
 * 
 */
struct sdk_basic_msg_user_verify_s {
    char device_verify_code[32];        ///< 设备验证码
    int result;                         ///< 验证结果
};

struct domain_basic_param_s {

};

class DomainBasic : public IDomain {
public:
    DomainBasic(const domain_basic_param_t &cfg);
    virtual ~DomainBasic();

    virtual bool app_request(const sdk_msg_t *request, sdk_msg_t *response) override;
};

} // namespace asty_gw_sdk
