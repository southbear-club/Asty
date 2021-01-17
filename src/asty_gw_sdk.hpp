/**
 * @file asty_gw_sdk.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-09
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <memory>
#include <string>
#include <functional>
#include "common/dev_sdk_errno.hpp"
#include "common/datatype.hpp"
#include "domain/domain.hpp"
#include "domain/core/core_def.hpp"

namespace asty_gw_sdk {

typedef struct sdk_param_s sdk_param_t;

struct sdk_param_s {
    std::string param;
};

class AstyGwSdk {
public:
    AstyGwSdk(const sdk_param_t &ini, const domain_core_init_t &core_cfg);
    ~AstyGwSdk();

    bool run(void);
    void stop(void);

public:
    /**
     * @brief 输出版本号
     * 
     * @return const char* 版本号
     */
    static const char *version(void);

    // 安装领域
    // sdk内置core领域，并在启动/安装后上报支持的领域
    bool install_domain(std::shared_ptr<IDomain> domain);

    // 卸载领域
    bool uninstall_domain(AstyGwDomainType domain_type);

private:
    std::shared_ptr<AstyGwSdkImpl> impl_;
};

}  // namespace asty_gw_sdk
