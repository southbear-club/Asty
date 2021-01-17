/**
 * @file net_def.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "../common/datatype.hpp"

namespace asty_gw_sdk
{

struct netif_host {
    std::string domain;     ///< 域名
    int port;               ///< 端口
};

} // namespace asty_gw_sdk
