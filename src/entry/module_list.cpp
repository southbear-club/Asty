/**
 * @file module_list.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-31
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "module_list.hpp"
#include "module/basic/module_manage/module_manage.hpp"
#include "module/open_api/device_gw/device_gateway.hpp"

namespace asty {

namespace entry {

static basic::ModuleManager module_manager(30);

void setup_module(void) {
    core::json_t param;

    module_manager.run({
        {ASTY_MODULE_REF(openapi_device_gateway), param},
    });
}

}  // namespace entry

}  // namespace asty
