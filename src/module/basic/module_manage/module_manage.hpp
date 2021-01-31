/**
 * @file module_manage.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-31
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <stddef.h>
#include <list>
#include <map>
#include <mutex>
#include "core/datatype.hpp"
#include "core/module.hpp"

namespace asty {

namespace basic {

// 模块注册信息
typedef struct {
    std::shared_ptr<core::IModule> module;  ///< 模块
    core::json_t param;                     ///< 模块初始化参数
} module_reg_t;

class ModuleManager {
public:
    ModuleManager(size_t module_max);
    ~ModuleManager();

    void run(const std::initializer_list<module_reg_t> &li);

    void stop(void);

    // 模块数量
    size_t module_count(void);

    // 模块信息列表
    std::list<core::module_base_info_t> module_list(void);

    // 模块信息查询
    core::module_base_info_t module_query(
        const core::module_identi_t &identifier);

    // 模块动态操作
    // 模块加载
    bool module_load(std::shared_ptr<core::IModule> module,
                     const core::json_t &param, core::json_t &res);

    // 模块卸载
    bool module_unload(const core::module_identi_t &identifier,
                       const core::json_t &param, core::json_t &res);

    // 模块启动
    bool module_start(const core::module_identi_t &identifier,
                      const core::json_t &param, core::json_t &res);

    // 模块停止
    bool module_stop(const core::module_identi_t &identifier,
                     const core::json_t &param, core::json_t &res);

    // 模块重启
    bool module_restart(const core::module_identi_t &identifier,
                        const core::json_t &param, core::json_t &res);

private:
    size_t module_max_;
    std::mutex mtx_;
    std::map<core::module_identi_t, std::shared_ptr<core::IModule>>
        modules_;  ///< 模块列表
};

}  // namespace basic

}  // namespace asty
