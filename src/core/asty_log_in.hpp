/**
 * @file asty_log_in.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <list>
#include <map>
#include <string>

namespace asty {

namespace core {

/**
 * @brief 日志等级
 *
 */
typedef enum {
    ASTY_INFO = 0,     ///< 调试等级
    ASTY_WARNING = 1,  ///< 警告等级
    ASTY_ERROR = 2,    ///< 错误
    ASTY_FATAL = 3     ///< 严重异常，将直接终止程序
} asty_log_lv;

/**
 * @brief 模块日志配置
 *
 */
struct asty_log_cfg_t {
    std::string module_name;  ///< 模块名称
    asty_log_lv lv;           ///< 日志等级
};

/**
 * @brief 日志模块
 *
 */
class AstyLog {
private:
    AstyLog(const char* proccess_name, const char* path);
    ~AstyLog();

public:
    /**
     * @brief 初始化
     *
     * @param proccess_name 程序名
     * @param path 日志路径
     */
    static void init(const char* proccess_name, const char* path);

    /**
     * @brief Set the up modules lv object
     *
     * @param module_conf 模块配置
     */
    static void setup_modules_lvl(const std::list<asty_log_cfg_t>& module_conf);

    /**
     * @brief Set the single module lv object
     *
     * @param module_name 模块名称
     * @param lv 日志等级
     */
    static void set_single_module_lvl(const char* module_name, asty_log_lv lv);

    /**
     * @brief 日志过滤期
     *
     * @param module_name 模块名称
     * @param lv_name 日志等级名称
     * @return true 过滤
     * @return false 不过滤
     */
    static bool filter(const char* module_name, const char* lv_name);

public:
    static const std::map<std::string, asty_log_lv> cfg_lv_map;  ///< 等级映射

private:
    static std::map<std::string, asty_log_lv> log_lv_map_;  ///< 模块映射
};

/**
 * @brief 检查日志使能，用于日志过滤
 *
 * @param module_name 模块名称
 * @param lv_name 检查的等级名称
 * @return true 使能
 * @return false 未使能
 */
bool asty_log_check_en(const char* module_name, const char* lv_name);

}  // namespace core

}  // namespace asty
