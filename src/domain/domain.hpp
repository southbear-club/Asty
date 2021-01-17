/**
 * @file domain.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>
#include "../common/micro_kernel/plugin.hpp"
#include "../common/datatype.hpp"
#include "domain_type.hpp"

namespace asty_gw_sdk
{

// 领域插件类型
using DomainPlugin = Asty::IPlugin<AstyGwDomainType>;

/**
 * @brief 领域信息
 * 
 */
struct DomainInfo {
    std::string name;
    std::string version;
    AstyGwDomainType type;
};

/**
 * @brief 领域抽象接口
 * 
 */
class IDomain {
public:
    IDomain(const DomainInfo &info) : domain_info_(info) {}
    virtual ~IDomain() { }

    // 用户消息请求接口
    virtual bool app_request(const sdk_msg_t *request, sdk_msg_t *response) = 0;

protected:
    friend class AstyGwSdkImpl;
    std::shared_ptr<DomainPlugin> get_plugin_ins(void) {
        return plugin_impl_;
    }

    const DomainInfo& get_domain_info(void) const {
        return domain_info_;
    }

protected:
    std::shared_ptr<DomainPlugin> plugin_impl_; ///< 插件实现
    DomainInfo domain_info_;
};

} // namespace asty_gw_sdk
