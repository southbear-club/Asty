/**
 * @file asty_gw_sdk_impl.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <atomic>
#include <memory>
#include "common/micro_kernel/micro_kernel.hpp"
#include "asty_gw_sdk.hpp"

namespace asty_gw_sdk {

class AstyGwSdkImpl {
public:
    AstyGwSdkImpl(const sdk_param_t &ini, const domain_core_init_t &core_cfg);
    ~AstyGwSdkImpl();

    bool run(void);
    void stop(void);

    // 安装领域
    // sdk内置core领域，并在启动/安装后上报支持的领域
    bool install_domain(std::shared_ptr<IDomain> domain);

    // 卸载领域
    bool uninstall_domain(AstyGwDomainType domain_type);

private:
    static std::atomic_bool created;

private:
    std::mutex mtx_;
    sdk_param_t param_;
    std::shared_ptr<Asty::MicroKernel<AstyGwDomainType>> micro_kernel_;
    std::map<AstyGwDomainType, std::shared_ptr<IDomain>> domains_;  ///< 存储领域节点避免领域只能指针被过早释放
};

}  // namespace asty_gw_sdk
