/**
 * @file domain_stream.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "../common/datatype.hpp"
#include "../common/micro_kernel/plugin.hpp"
#include "../domain/domain_type.hpp"

using namespace Asty;

namespace asty_gw_sdk {

class DomainStream : public IPluginStream<AstyGwDomainType> {
public:
    DomainStream(const PluginKey<AstyGwDomainType> &from,
                 const PluginKey<AstyGwDomainType> &to)
        : IPluginStream<AstyGwDomainType>(from, to) {}

    // 关闭流式通信连接
    virtual void close() override { return; }

    // 检查连接是否关闭
    virtual bool is_closed(void) override { return false; }

    // 发送数据
    virtual int send(const PluginDataT &data, const time_t wait = -1) override {
        return 0;
    }

    // 接收数据
    virtual int recv(PluginDataT &data, const time_t wait = -1) override {
        return 0;
    }
};

}
