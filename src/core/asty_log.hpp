/**
 * @file asty_log.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <cstring>
#include <fstream>

namespace asty {

namespace core {

#define DEFAULT_ASTY_MODULE_NAME "NON"

#ifndef ASTY_MODULE_NAME
#define ASTY_MODULE_NAME DEFAULT_ASTY_MODULE_NAME
#endif

/**
 * @brief 输入到空洞，没有任何效果
 *
 */
struct NullLog {
    // 输出流引用
    static std::ofstream& stream(void) {
        // 线程单例
        thread_local NullLog null_log;
        return null_log.null_stream_;
    }
    void operator&(std::ostream&) {}

public:
    NullLog() {}

private:
    std::ofstream null_stream_;  // 不写文件名，类似于/dev/null
};

/**
 * @brief 日志等级名称
 * @details 只能使用这些等级
 *
 */
struct AstyLogLvName {
    constexpr static const char* INFO = "INFO";
    constexpr static const char* WARNING = "WARNING";
    constexpr static const char* ERROR = "ERROR";
    constexpr static const char* FATAL = "FATAL";
};

extern bool asty_log_check_en(const char* module_name, const char* lv_name);

/**
 * @brief 日志输出，@ref AstyLogLvName
 *
 */
#define ASTY_LOG(severity)                                                     \
    if (!asty::core::asty_log_check_en(ASTY_MODULE_NAME,                       \
                                       asty::core::AstyLogLvName::severity)) { \
    } else                                                                     \
        LOG(severity) << "[" ASTY_MODULE_NAME "] "

/**
 * @brief 条件满足时输出
 *
 */
#define ASTY_LOG_IF(severity, cond)                                            \
    if (!asty::core::asty_log_check_en(ASTY_MODULE_NAME,                       \
                                       asty::core::AstyLogLvName::severity)) { \
    } else                                                                     \
        LOG_IF(severity, cond) << "[" ASTY_MODULE_NAME "] "

}  // namespace core

}  // namespace asty
