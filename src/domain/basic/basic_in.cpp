/**
 * @file basic_in.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include "basic_in.hpp"

namespace asty_gw_sdk {

using namespace Asty;

static const PluginKey<AstyGwDomainType> plugin_basic_key {
    DOMAIN_BASIC_NAME,
    DOMAIN_BASIC_VERSION,
    E_ASTY_GW_DOMAIN_BASIC
};

DomainBasicPlugin::DomainBasicPlugin(const domain_basic_param_t &param)
    : IPlugin<AstyGwDomainType>(plugin_basic_key), param_(param) {}

DomainBasicPlugin::~DomainBasicPlugin() {

}

// 初始化
bool DomainBasicPlugin::plugin_init(void) {
    return true;
}

// 启动
bool DomainBasicPlugin::plugin_start(void) {
    return true;
}

// cycle调用
bool DomainBasicPlugin::plugin_task(void) {
    std::cout << "basic running .... " << std::endl;
    return true;
}

bool DomainBasicPlugin::plugin_task_en(void) {
    return true;
}

// 停止
bool DomainBasicPlugin::plugin_stop(void) {
    return true;
}

// 退出
bool DomainBasicPlugin::plugin_exit(void) {
    return true;
}

// 消息通知，来自微内核
bool DomainBasicPlugin::notice(const PluginDataT &msg) {
    return true;
}

// 消息处理
bool DomainBasicPlugin::message(const PluginMessage<AstyGwDomainType> &request,
                        PluginMessage<AstyGwDomainType> &response) {
    return true;
}

// 流式消息处理
bool DomainBasicPlugin::stream(
    std::shared_ptr<IPluginStream<AstyGwDomainType>> &stream) {
    return true;
}

}
