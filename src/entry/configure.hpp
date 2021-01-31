/**
 * @file configure.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

namespace asty
{

// 运行时目录
#ifndef ASTY_RT_ROOT_PATH
    #define ASTY_RT_ROOT_PATH "apsd_rt"
#endif // !ASTY_RT_ROOT_PATH

// 能力集文件路径
#define ASTY_CAPABILITY_FILENAME ASTY_RT_ROOT_PATH "/etc/asty_capability.json"
// 配置文件路径
#define ASTY_CONFIG_FILENAME ASTY_RT_ROOT_PATH "/etc/asty_parameter.json"
// 日志路径
#define ASTY_LOG_PATH ASTY_RT_ROOT_PATH "/log/"
// coredump生成路径
#define ASTY_COREDUMP_PATH ASTY_RT_ROOT_PATH "/coredump/"
// pid路径
#define PID_FILE "/var/run/asty.pid"

} // namespace asty
