/**
 * @file asty_config.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "common/utils/asty_lock.hpp"
#include "common/common.hpp"
#include "datatype.hpp"

namespace asty {

namespace core {

/**
 * @brief 参数配置
 *
 */
class AstyParameter {
public:
    /**
     * @brief 配置初始化
     *
     * @param path 配置文件路径
     */
    static void init(const std::string &path);

    /**
     * @brief Get the Instance object
     *
     * @param path 配置文件路径，只需要第一次调用传入
     * @return AstyParameter& 配置参数对象应用
     */
    static AstyParameter &get_instance(const std::string &path = "");

    /**
     * @brief 获取json参数引用
     *
     * @return json_t&
     */
    json_t &parameter_ref(void);

    /**
     * @brief 固化到磁盘
     *
     * @return true
     * @return false
     */
    bool dump(void);

    /**
     * @brief 固化到磁盘
     *
     * @param param 指定配置参数
     * @return true
     * @return false
     */
    bool dump(const json_t &param);

    /**
     * @brief 获取读写锁引用
     *
     * @return RwMutex&
     */
    utils::RwMutex &lock() { return mtx_; }

private:
    AstyParameter(const std::string &path);

    DISALLOW_COPY_AND_ASSIGN(AstyParameter);

private:
    utils::RwMutex mtx_;  ///< 读写锁
    std::string path_;    ///< 配置路径
    json_t param_;        ///< 参数
};

/**
 * @brief 获取参数值，只用该接口去获取
 * @param key 为json的key和正常使用方式相同
 */
#define GET_PARAM_ONCE(key)                                           \
    ({                                                                \
        asty::utils::RMutexGuard lck(                                 \
            asty::core::AstyParameter::get_instance().lock());        \
        asty::core::AstyParameter::get_instance().parameter_ref() key; \
    })

/**
 * @brief 设置参数值，只用该接口去设置
 * @param key 为json的key和正常使用方式相同
 */
#define SET_PARAM_ONCE(key, value)                                            \
    ({                                                                        \
        asty::utils::WMutexGuard lck(                                         \
            asty::core::AstyParameter::get_instance().lock());                \
        asty::core::AstyParameter::get_instance().parameter_ref() key = value; \
        asty::core::AstyParameter::get_instance().dump();                     \
    })

// TODO
#define PARAM_CONTAINS(one_key)

}  // namespace core

}  // namespace asty
