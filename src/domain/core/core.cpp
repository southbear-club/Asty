/**
 * @file core.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include "core.hpp"

namespace asty_gw_sdk {

using namespace Asty;

static const PluginKey<AstyGwDomainType> plugin_core_key {
    "core",
    "1.0.0",
    E_ASTY_GW_DOMAIN_CORE
};

DomainCore::DomainCore(const domain_core_init_t &ini)
    : IPlugin<AstyGwDomainType>(plugin_core_key) {}

DomainCore::~DomainCore() {

}

// 初始化
bool DomainCore::plugin_init(void) {
    return true;
}

// 启动
bool DomainCore::plugin_start(void) {
    return true;
}

// cycle调用
bool DomainCore::plugin_task(void) {
    std::cout << "core running .... " << std::endl;
    return true;
}

bool DomainCore::plugin_task_en(void) {
    return true;
}

// 停止
bool DomainCore::plugin_stop(void) {
    return true;
}

// 退出
bool DomainCore::plugin_exit(void) {
    return true;
}

// 消息通知，来自微内核
bool DomainCore::notice(const PluginDataT &msg) {
    return true;
}

// 消息处理
bool DomainCore::message(const PluginMessage<AstyGwDomainType> &request,
                        PluginMessage<AstyGwDomainType> &response) {
    return true;
}

// 流式消息处理
bool DomainCore::stream(
    std::shared_ptr<IPluginStream<AstyGwDomainType>> &stream) {
    return true;
}

}