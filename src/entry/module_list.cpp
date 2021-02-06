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
#include "common/functions/database/database.hpp"
#include "module/basic/module_manage/module_manage.hpp"
#include "module/basic/user_manage/user_manager_module.hpp"
#include "module/open_api/device_gw/device_gateway.hpp"

namespace asty {

namespace entry {

static basic::ModuleManager module_manager(30);

void setup_module(void) {
    core::json_t param;
    static mongocxx::instance mongo_instance{};
    mongocxx::client mongo_client{mongocxx::uri{"mongodb://platform:905984143w@172.27.20.178:27017/astyCloudPlatform"}};

    module_manager.run({
        {ASTY_MODULE_REF(basic_user_manager), &mongo_client},
        {ASTY_MODULE_REF(openapi_device_gateway), &param},
    });
}

}  // namespace entry

}  // namespace asty
