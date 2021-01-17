/**
 * @file basic.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "basic_in.hpp"
#include "basic.hpp"

namespace asty_gw_sdk {

static const DomainInfo domain_basic_key {
    DOMAIN_BASIC_NAME,
    DOMAIN_BASIC_VERSION,
    E_ASTY_GW_DOMAIN_BASIC
};

DomainBasic::DomainBasic(const domain_basic_param_t &cfg)
    : IDomain(domain_basic_key) {
    plugin_impl_ = std::make_shared<DomainBasicPlugin>(cfg);
}

DomainBasic::~DomainBasic() {}

bool DomainBasic::app_request(const sdk_msg_t *request, sdk_msg_t *response) {
    // TODO
    return true;
}

}
