/**
 * @file ut_main.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../src/asty_gw_sdk.hpp"
#include "../src/domain/basic/basic.hpp"

using namespace asty_gw_sdk;

int main(void) {
    sdk_param_t ini;
    domain_core_init_t core_param;
    domain_basic_param_t basic_param;

    std::shared_ptr<AstyGwSdk> sdk(new AstyGwSdk(ini, core_param));

    std::shared_ptr<DomainBasic> basic(new DomainBasic(basic_param));

    sdk->install_domain(basic);

    sdk->run();

    return 0;
}