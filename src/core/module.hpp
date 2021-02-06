/**
 * @file module.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 模块管理
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>
#include <stdint.h>
#include <memory>
#include "datatype.hpp"

namespace asty {

namespace core
{

// 模块状态
typedef enum {
    E_MODULE_ST_STOP = 0,       ///< 停止
    E_MODULE_ST_RUNNING = 1,    ///< 运行中
    E_MODULE_ST_BAD = 2,        ///< 异常
} module_st_t;

// 模块权限
typedef enum {
    E_MODULE_PER_NO = 0,        ///< 无权限
    E_MODULE_PER_VIEWER = 1,    ///< 可视权限
    E_MODULE_PER_USER = 2,      ///< 普通权限
    E_MODULE_PER_ADMIN = 3,     ///< 超级权限
} module_permission_t;

// 模块分组
typedef enum {
    E_MODULE_GROUP_CORE = 0,     ///< 系统核心模块
    E_MODULE_GROUP_BASIC = 1,    ///< 基础组件
    E_MODULE_GROUP_SERVICE = 2,  ///< 服务组件
    E_MODULE_GROUP_OPENAPI = 3,  ///< 开放API组件
} module_group_t;

// 模块分类
typedef enum {
    E_MODULE_TYPE_SYS = 0,      ///< 系统管理
    E_MODULE_TYPE_DATA = 1,     ///< 数据管理
    E_MODULE_TYPE_NET = 2,      ///< 网络相关
    E_MODULE_TYPE_STORAGE = 3,  ///< 存储
    E_MODULE_TYPE_ACCESS = 4,   ///< 接入
} module_type_t;

using module_identi_t = std::string;

/**
 * @brief 模块基本信息
 * 
 */
typedef struct {
    std::string name;           ///< 模块名称
    std::string desc;           ///< 模块描述
    std::string version;        ///< 模块版本
    bool enable;                ///< 使能
    module_identi_t identifier;         ///< 标识，由初始加载时进行分配一个，模块自身不用去填写
    module_type_t type;                 ///< 模块类别
    module_group_t group;               ///< 分组
    module_permission_t permission;     ///< 权限
} module_base_info_t;

// 模块定义
class IModule {
public:
    IModule(const module_base_info_t &info) : info_(info) {}
    virtual ~IModule() {}

    virtual bool init(void *param) = 0;
    virtual bool start(void *param) = 0;
    virtual bool stop(void *param) = 0;
    virtual bool exit(void *param) = 0;

    virtual module_st_t status(void) {
        return st_;
    }

    virtual void set_status(module_st_t st) {
        st_ = st;
    }

    virtual module_base_info_t module_info(void) {
        return info_;
    }

    virtual void set_identifier(const std::string &identi) {
        info_.identifier = identi;
    }

public:
    module_base_info_t info_;   ///< 模块基本信息
    module_st_t st_;               ///< 模块状态
};

// 定义模块引用接口
#define DEFINE_ASTY_MODULE_REF(name) std::shared_ptr<asty::core::IModule> _asty_##name##_module_object_ref(void)
// 模块引用
#define ASTY_MODULE_REF(name) asty::_asty_##name##_module_object_ref()
    
} // namespace core

} // namespace asty
