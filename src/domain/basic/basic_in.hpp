/**
 * @file basic_in.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "basic.hpp"
#include "../domain.hpp"

namespace asty_gw_sdk {

using namespace Asty;

#define DOMAIN_BASIC_NAME "basic"
#define DOMAIN_BASIC_VERSION "1.0.0"

class DomainBasicPlugin : public DomainPlugin {
public:
    DomainBasicPlugin(const domain_basic_param_t &param);
    virtual ~DomainBasicPlugin();

    // 初始化
    virtual bool plugin_init(void) override;

    // 启动
    virtual bool plugin_start(void) override;

    // cycle调用
    virtual bool plugin_task(void) override;

    virtual bool plugin_task_en(void) override;

    // 停止
    virtual bool plugin_stop(void) override;

    // 退出
    virtual bool plugin_exit(void) override;

    // 消息通知，来自微内核
    virtual bool notice(const PluginDataT &msg) override;

    // 消息处理
    virtual bool message(const PluginMessage<AstyGwDomainType> &request,
                         PluginMessage<AstyGwDomainType> &response) override;

    // 流式消息处理
    virtual bool stream(
        std::shared_ptr<IPluginStream<AstyGwDomainType>> &stream) override;

private:
    domain_basic_param_t param_;
};

}
