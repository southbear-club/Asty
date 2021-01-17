/**
 * @file asty_gw_sdk.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "asty_gw_sdk_impl.hpp"
#include "asty_gw_sdk.hpp"

#ifndef SOFT_VERSION
#define SOFT_VERSION "v0.0.0"
#endif

namespace asty_gw_sdk {

// core
// basic
//  - 设备注册/验证
//  - 设备绑定
//  - 设备能力
//  - 网络
//  - dns
// alarm
//  - 报警
// media
//  - 直播
//  - 录像
//  - 回放
//  - 对讲
//  - 视频控制
//  - 拍照
//  - 图片上传
// device control
//  - 设备控制
// transport
// spec
//  - 识别

AstyGwSdk::AstyGwSdk(const sdk_param_t &ini, const domain_core_init_t &core_cfg) {
    impl_ = std::make_shared<AstyGwSdkImpl>(ini, core_cfg);
}

AstyGwSdk::~AstyGwSdk() {

}

bool AstyGwSdk::run(void) {
    return impl_->run();
}

void AstyGwSdk::stop(void) {
    impl_->stop();
}

const char *AstyGwSdk::version(void) {
    return SOFT_VERSION;
}

// sdk内置core领域，并在启动/安装后上报支持的领域
bool AstyGwSdk::install_domain(std::shared_ptr<IDomain> domain) {
    return impl_->install_domain(domain);
}

// 卸载领域
bool AstyGwSdk::uninstall_domain(AstyGwDomainType domain_type) {
    return impl_->uninstall_domain(domain_type);
}

}  // namespace asty_gw_sdk