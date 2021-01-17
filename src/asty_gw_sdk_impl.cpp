/**
 * @file asty_gw_sdk_impl.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * 1. 初始化网络配置
 * 2. 初始化设备信息
 * 3. 初始化领域信息
 */

#include "domain/core/core.hpp"
#include "asty_gw_sdk_impl.hpp"

namespace asty_gw_sdk {

using namespace Asty;

std::atomic_bool AstyGwSdkImpl::created(true);

AstyGwSdkImpl::AstyGwSdkImpl(const sdk_param_t &ini, const domain_core_init_t &core_cfg) : param_(ini) {
    // 创建线程池
    std::shared_ptr<MicroKernelThreadPool> thread_pool(new MicroKernelThreadPool);

    // 创建微内核
    micro_kernel_ = std::make_shared<MicroKernel<AstyGwDomainType>>(100, thread_pool);

    // 内置核心领域
    std::shared_ptr<DomainCore> core(new DomainCore(core_cfg));

    // 安装核心领域
    micro_kernel_->plugin_register(core);
}

AstyGwSdkImpl::~AstyGwSdkImpl() {

}

bool AstyGwSdkImpl::run(void) {
    micro_kernel_->run();
    return true;
}

void AstyGwSdkImpl::stop(void) {
}

// sdk内置core领域，并在启动/安装后上报支持的领域
bool AstyGwSdkImpl::install_domain(std::shared_ptr<IDomain> domain) {
    std::unique_lock<std::mutex> lck(mtx_);
    auto info = domain->get_domain_info();

    auto item = domains_.find(info.type);

    if (item != domains_.end()) {
        return false;
    }

    domains_.insert(std::pair<AstyGwDomainType, std::shared_ptr<IDomain>>(info.type, domain));
    lck.unlock();

    return micro_kernel_->plugin_register(domain->get_plugin_ins());
}

// 卸载领域
bool AstyGwSdkImpl::uninstall_domain(AstyGwDomainType domain_type) {
    std::unique_lock<std::mutex> lck(mtx_);
    auto item = domains_.find(domain_type);

    if (item != domains_.end()) {
        return false;
    }

    domains_.erase(item);
    lck.unlock();

    return micro_kernel_->plugin_unregister(domain_type);
}

}
