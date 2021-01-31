/**
 * @file device_gateway.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "device_gateway.hpp"
namespace asty {

namespace op_dev_gw {

static const core::module_base_info_t in_module_info {
    "device gateway",
    "open api of device gateway",
    "1.0.0",
    true,
    "",
    core::E_MODULE_TYPE_ACCESS,
    core::E_MODULE_GROUP_OPENAPI,
    core::E_MODULE_PER_USER,
};

DeviceGwOpenApiModule::DeviceGwOpenApiModule() : core::IModule(in_module_info) {

}

DeviceGwOpenApiModule::~DeviceGwOpenApiModule() {

}

}  // namespace op_dev_gw

DEFINE_ASTY_MODULE_REF(openapi_device_gateway) {
    static bool init = false;
    if (init) {
        return nullptr;
    }

    init = true;
    std::shared_ptr<core::IModule> module(new op_dev_gw::DeviceGwOpenApiModule);

    return module;
}

}  // namespace asty

