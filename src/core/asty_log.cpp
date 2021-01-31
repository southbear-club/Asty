/**
 * @file asty_log.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "asty_log_in.hpp"
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <map>
#include <stdexcept>
#include <iostream>

namespace asty
{

namespace core
{

const std::map<std::string, asty_log_lv> AstyLog::cfg_lv_map = {
    {"INFO", ASTY_INFO},
    {"WARNING", ASTY_WARNING},
    {"ERROR", ASTY_ERROR},
    {"FATAL", ASTY_FATAL},
};

std::map<std::string, asty_log_lv> AstyLog::log_lv_map_;

AstyLog::AstyLog(const char* proccess_name, const char* path) {
    google::InitGoogleLogging(proccess_name);

#ifdef DEBUG
    // 输出到标准输出而不是文件
    FLAGS_logtostderr = true;
    // 除了输出到文件，也输出到终端
    FLAGS_alsologtostderr = true;
#else
    FLAGS_logtostderr = false;
    FLAGS_alsologtostderr = false;
#endif

    if (path) {
        // 换从时间,0s-实时输出
        FLAGS_logbufsecs = 0;
        // 日志文件分割大小限制5M
        FLAGS_max_log_size = 5;
        // 磁盘写满时不再写日志
        FLAGS_stop_logging_if_full_disk = true;
        // 日志记录位置
        FLAGS_log_dir = path;
        // 日志文件添加扩展名
        // google::SetLogFilenameExtension("asty");
        // google::SetLogDestination(google::GLOG_ERROR, "log/prefix_");
    } else {
        FLAGS_logtostderr = true;
        FLAGS_alsologtostderr = true;
    }

    // 打印色彩
    FLAGS_colorlogtostderr = true;
    FLAGS_minloglevel = google::GLOG_INFO;

    // 占位
    log_lv_map_["asty-none-log"] = ASTY_FATAL;
}

AstyLog::~AstyLog() { google::ShutdownGoogleLogging(); }

void AstyLog::init(const char* proccess_name, const char* path) {
    static AstyLog log(proccess_name, path);
}

void AstyLog::setup_modules_lvl(const std::list<asty_log_cfg_t>& module_conf) {
    for (auto& item : module_conf) {
        log_lv_map_.insert(
            std::pair<std::string, asty_log_lv>(item.module_name, item.lv));
    }
}

void AstyLog::set_single_module_lvl(const char* module_name, asty_log_lv lv) {
    if (!module_name) {
        return;
    }

    log_lv_map_[module_name] = lv;
}

bool AstyLog::filter(const char* module_name, const char* lv_name) {
    if (!module_name || !lv_name) {
        return true;
    }

    if (log_lv_map_.empty()) {
        throw std::logic_error("please init log first.");
    }

    auto m1 = cfg_lv_map.find(lv_name);
    if (m1 == cfg_lv_map.end()) {
        return true;
    }

    auto m2 = log_lv_map_.find(module_name);
    if (m2 == log_lv_map_.end()) {
        // 没找到模块则使用最严格的日志等级
        return m1->second < ASTY_FATAL;
    }

    // 比配置的日志等级宽松就过滤掉
    return m1->second < m2->second;
}

bool asty_log_check_en(const char* module_name, const char* lv_name) {
    return !AstyLog::filter(module_name, lv_name);
}

} // namespace core

} // namespace asty
