/**
 * @file core.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 核心领域
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "../../common/micro_kernel/plugin.hpp"
#include "../../asty_gw_sdk.hpp"
#include "../domain_type.hpp"
#include "core_def.hpp"

namespace asty_gw_sdk {

using namespace Asty;

class DomainCore : public IPlugin<AstyGwDomainType> {
public:
    DomainCore(const domain_core_init_t &ini);
    virtual ~DomainCore();

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
};

}
