/**
 * @file datatype.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <string>

namespace asty_gw_sdk
{

class AstyGwSdkImpl;
typedef struct sdk_msg_s sdk_msg_t;

struct sdk_msg_s {
    size_t len;
    void *msg;
};

} // namespace asty_gw_sdk
