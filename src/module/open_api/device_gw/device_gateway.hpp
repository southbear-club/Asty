/**
 * @file device_gateway.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-31
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include "core/module.hpp"

namespace asty {

namespace op_dev_gw {

class DeviceGwOpenApiModule : public core::IModule {
public:
    DeviceGwOpenApiModule();
    virtual ~DeviceGwOpenApiModule();

    virtual bool init(void *param) override { return true; }

    virtual bool start(void *param) override { return true; }

    virtual bool stop(void *param) override { return true; }

    virtual bool exit(void *param) override { return true; }
};

}  // namespace op_dev_gw

DEFINE_ASTY_MODULE_REF(openapi_device_gateway);

}  // namespace asty
