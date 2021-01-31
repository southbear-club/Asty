/**
 * @file log_cfg.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "log_cfg.hpp"
#include "core/asty_config.hpp"
#include "core/asty_log_in.hpp"

namespace asty {

namespace entry {

/**
 * @brief 添加模块集日志配置
 *
 * @param list 配置列表
 * @param set 模块集
 */
static void add_module_set_log_cfg(std::list<core::asty_log_cfg_t> &list,
                               core::json_t &set) {
    // 遍历子模块
    for (auto &item : set.items()) {
        // 判断是否配置日志
        if (item.value().contains("log lv")) {
            // 查找对应等级
            auto lv = core::AstyLog::cfg_lv_map.find(item.value()["log lv"]);
            if (lv != core::AstyLog::cfg_lv_map.end()) {
                core::asty_log_cfg_t cfg = {item.key(), lv->second};
                // 添加模块等级
                list.push_back(cfg);
            }
        }

        // 有子模块递归添加
        if (item.value().contains("has submodule") && item.value().is_object()) {
            add_module_set_log_cfg(list, item.value());
        }
    }
}

/**
 * @brief 解析日志等级
 *
 * @return std::list<asty_log_cfg_t> 日志等级配置列表
 */
static std::list<core::asty_log_cfg_t> parser_log_lvl(void) {
    std::list<core::asty_log_cfg_t> cfg;

    // XXX:顶级起始配置，只能由这几个开始
    // 系统参数
    auto sys_param = GET_PARAM_ONCE(["system"]);
    // 模块参数
    // 基础模块
    auto basic_module_param = GET_PARAM_ONCE(["module"]["basic"]);
    // 服务模块
    auto services_module_param = GET_PARAM_ONCE(["module"]["services"]);
    // 开放api
    auto openapi_module_param = GET_PARAM_ONCE(["module"]["open api"]);

    add_module_set_log_cfg(cfg, sys_param);
    add_module_set_log_cfg(cfg, basic_module_param);
    add_module_set_log_cfg(cfg, services_module_param);
    add_module_set_log_cfg(cfg, openapi_module_param);

    return cfg;
}

void config_log_lvl(void) { core::AstyLog::setup_modules_lvl(parser_log_lvl()); }

}  // namespace entry

}  // namespace asty
