/**
 * @file dev_sdk_errno.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

namespace asty_gw_sdk
{

typedef enum {
    sdk_err_ok              = 0,
    sdk_err_base            = 0xe0000000,
    sdk_err_core            = sdk_err_base + 0x10000,
    sdk_err_basic           = sdk_err_base + 0x20000,
    sdk_err_alarm           = sdk_err_base + 0x30000,
    sdk_err_media           = sdk_err_base + 0x40000,
    sdk_err_devctrl         = sdk_err_base + 0x50000,
    sdk_err_transport       = sdk_err_base + 0x60000,
    sdk_err_spec            = sdk_err_base + 0x70000,
} sdk_errno_t;

} // namespace asty_gw_sdk
