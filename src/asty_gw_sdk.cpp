/**
 * @file asty_gw_sdk.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "asty_gw_sdk.hpp"

#ifndef SOFT_VERSION
#define SOFT_VERSION "v0.0.0"
#endif

namespace asty_gw_sdk {

const char* sdk_version(void) {
    return SOFT_VERSION;
}

}  // namespace asty_gw_sdk