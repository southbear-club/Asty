/**
 * @file log.h
 * @author wotsen (astralrovers@outlook.com)
 * @brief 日志
 * @date 2021-01-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <glog/logging.h>
#include <glog/raw_logging.h>

#ifndef ASTY_GW_SDK_LOG_NAME
#define ASTY_GW_SDK_LOG_NAME "non"
#endif // !ASTY_GW_SDK_LOG_NAME

#define ASTY_LOG(V) LOG(V) << "[ASTY-GW-SDK|" ASTY_GW_LOG_NAME "]"
#define ASTY_LOG_IF(V, cond) LOG(V, cond) << "[ASTY-GW-SDK|" ASTY_GW_LOG_NAME "]"