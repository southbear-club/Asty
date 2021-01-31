/**
 * @file module_manage.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-31
 *
 * @copyright Copyright (c) 2021
 *
 */
#define ASTY_MODULE_NAME "module manager"
#include "module_manage.hpp"
#include <stdio.h>
#include "common/utils/asty_md5.hpp"
#include "core/asty_log.hpp"

namespace asty {

namespace basic {

static core::module_identi_t _gen_module_identifier(const core::module_base_info_t &info) {
    std::string data = info.name + info.version + std::to_string(info.type) + std::to_string(info.group);
    uint8_t md5[16] = "";
    char identi[33] = "";

    utils::md5_t mobj;
    utils::md5_init(&mobj);
    utils::md5_update(&mobj, data.c_str(), data.size());
    utils::md5_final(md5, &mobj);

    for (int i = 0; i < 16; i++) {
        sprintf(identi + i * 2, "%02x", md5[i]);
    }

    return identi;
}

ModuleManager::ModuleManager(size_t module_max) : module_max_(module_max) {}

ModuleManager::~ModuleManager() {}

void ModuleManager::run(const std::initializer_list<module_reg_t> &li) {
    size_t cnt = 0;
    core::json_t res;
    core::json_t param;

    for (auto &item : li) {
        if (cnt > module_max_) {
            ASTY_LOG(WARNING) << "module limit : " << module_max_
                              << " but give : " << li.size() << "\n";
            break;
        }
        cnt++;

        if (!item.module->init(item.param, res)) {
            item.module->set_status(core::E_MODULE_ST_BAD);
            ASTY_LOG(WARNING) << "module : " << item.module->module_info().name
                              << "init failed\n";
            continue;
        }

        core::module_identi_t identi = _gen_module_identifier(item.module->module_info());
        item.module->set_identifier(identi);
        modules_.insert(
            std::pair<core::module_identi_t, std::shared_ptr<core::IModule>>(
                identi, item.module));
    }

    for (auto &item : modules_) {
        if (!item.second->start(param, res)) {
            // 启动失败则标记为异常
            item.second->set_status(core::E_MODULE_ST_BAD);
            ASTY_LOG(WARNING) << "module : " << item.second->module_info().name
                              << "start failed\n";
        } else {
            ASTY_LOG(INFO) << "module : [" << item.second->module_info().name << "] identi : [" << item.second->module_info().identifier << "] running\n";
            item.second->set_status(core::E_MODULE_ST_RUNNING);
        }
    }

    ASTY_LOG(INFO) << "total module : " << module_count() << "\n";
}

void ModuleManager::stop(void) {
    core::json_t res;
    core::json_t param;

    for (auto &item : modules_) {
        if (core::E_MODULE_ST_RUNNING == item.second->status()) {
            item.second->stop(param, res);
            item.second->set_status(core::E_MODULE_ST_STOP);
        }
    }
}

// 模块数量
size_t ModuleManager::module_count(void) { return modules_.size(); }

// 模块信息列表
std::list<core::module_base_info_t> ModuleManager::module_list(void) {
    std::unique_lock<std::mutex> lck(mtx_);
    std::list<core::module_base_info_t> li;

    for (auto &item : modules_) {
        li.push_back(item.second->module_info());
    }

    return li;
}

// 模块信息查询
core::module_base_info_t ModuleManager::module_query(
    const core::module_identi_t &identifier) {
    static const core::module_base_info_t in_module_info{
        "invalid module",
        "invalid module",
        "0.0.0",
        false,
        "invalid",
        core::E_MODULE_TYPE_ACCESS,
        core::E_MODULE_GROUP_OPENAPI,
        core::E_MODULE_PER_USER,
    };
    std::unique_lock<std::mutex> lck(mtx_);
    auto key = modules_.find(identifier);

    if (key == modules_.end()) {
        ASTY_LOG(WARNING) << "not find module : " << identifier << "\n";
        return in_module_info;
    }

    return key->second->module_info();
}

// 模块动态操作
// 模块加载
bool ModuleManager::module_load(std::shared_ptr<core::IModule> module,
                                const core::json_t &param, core::json_t &res) {
    if (!module->init(param, res)) {
        module->set_status(core::E_MODULE_ST_BAD);
        ASTY_LOG(WARNING) << "module : " << module->module_info().name
                            << "init failed\n";
        return false;
    }

    core::module_identi_t identi = _gen_module_identifier(module->module_info());
    module->set_identifier(identi);
    modules_.insert(
        std::pair<core::module_identi_t, std::shared_ptr<core::IModule>>(identi, module));

    return true;
}

// 模块卸载
bool ModuleManager::module_unload(const core::module_identi_t &identifier,
                                  const core::json_t &param,
                                  core::json_t &res) {
    std::unique_lock<std::mutex> lck(mtx_);
    auto item = modules_.find(identifier);

    if (item != modules_.end()) {
        ASTY_LOG(WARNING) << "not find module : " << identifier << "\n";
        return false;
    }

    item->second->stop(param, res);
    item->second->exit(param, res);

    // 直接俄删除
    modules_.erase(item);

    return true;
}

// 模块启动
bool ModuleManager::module_start(const core::module_identi_t &identifier,
                                 const core::json_t &param, core::json_t &res) {
    std::unique_lock<std::mutex> lck(mtx_);
    auto item = modules_.find(identifier);

    if (item != modules_.end()) {
        ASTY_LOG(WARNING) << "not find module : " << identifier << "\n";
        return false;
    }

    if (core::E_MODULE_ST_STOP == item->second->status()) {
        if (!item->second->start(param, res)) {
            // 启动失败则标记为异常
            item->second->set_status(core::E_MODULE_ST_BAD);
            ASTY_LOG(WARNING) << "module : " << item->second->module_info().name << "start failed\n";
            return false;
        }

        ASTY_LOG(INFO) << "module : [" << item->second->module_info().name << "] identi : [" << item->second->module_info().identifier << "] running\n";
        item->second->set_status(core::E_MODULE_ST_RUNNING);
        return true;
    }

    return false;
}

// 模块停止
bool ModuleManager::module_stop(const core::module_identi_t &identifier,
                                const core::json_t &param, core::json_t &res) {
    std::unique_lock<std::mutex> lck(mtx_);
    auto item = modules_.find(identifier);

    if (item != modules_.end()) {
        ASTY_LOG(WARNING) << "not find module : " << identifier << "\n";
        return false;
    }

    if (core::E_MODULE_ST_RUNNING == item->second->status()) {
        if (!item->second->stop(param, res)) {
            item->second->set_status(core::E_MODULE_ST_BAD);
            ASTY_LOG(WARNING) << "module : " << item->second->module_info().name << "stop failed\n";
            return false;
        }

        item->second->set_status(core::E_MODULE_ST_STOP);
        return true;
    }

    return false;
}

// 模块重启
bool ModuleManager::module_restart(const core::module_identi_t &identifier,
                                   const core::json_t &param,
                                   core::json_t &res) {
    std::unique_lock<std::mutex> lck(mtx_);
    auto item = modules_.find(identifier);

    if (item != modules_.end()) {
        ASTY_LOG(WARNING) << "not find module : " << identifier << "\n";
        return false;
    }

    if (core::E_MODULE_ST_BAD == item->second->status()) {
        ASTY_LOG(WARNING) << "module : " << item->second->module_info().name << "is bad\n";
    }

    if (core::E_MODULE_ST_RUNNING == item->second->status()) {
        item->second->stop(param, res);
    }

    // 强制置为为停止状态
    item->second->set_status(core::E_MODULE_ST_STOP);
    if (item->second->start(param, res)) {
        item->second->set_status(core::E_MODULE_ST_RUNNING);
        return true;
    }

    item->second->set_status(core::E_MODULE_ST_BAD);
    ASTY_LOG(WARNING) << "module : " << item->second->module_info().name << "restart failed\n";
    return false;
}

}  // namespace basic

}  // namespace asty
