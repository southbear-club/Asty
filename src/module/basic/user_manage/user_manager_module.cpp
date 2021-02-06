/**
 * @file user_manager_module.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "user_manager_module.hpp"
#include "user_manage_impl.hpp"
#include "user_db_impl.hpp"

namespace asty {

namespace basic {

static const core::module_base_info_t in_module_info {
    "user manager",
    "user manage, CURD users",
    "1.0.0",
    true,
    "",
    core::E_MODULE_TYPE_DATA,
    core::E_MODULE_GROUP_BASIC,
    core::E_MODULE_PER_USER,
};

UserManagerModule::UserManagerModule() : core::IModule(in_module_info), user_ma_(nullptr) {

}

UserManagerModule::~UserManagerModule() {

}

bool UserManagerModule::init(void *db) {
    if (!db || user_ma_) {
        return false;
    }

    std::shared_ptr<IUserDb> user_db(new UserDbImpl((mongocxx::client*)db));
    user_ma_ = new UserManager(user_db);
    return true;
}

bool UserManagerModule::start(void *param) { return true; }

bool UserManagerModule::stop(void *param) { return true; }

bool UserManagerModule::exit(void *param) {
    if (user_ma_) {
        delete user_ma_;
        user_ma_ = nullptr;
    }

    return true;
}

}  // namespace basic

DEFINE_ASTY_MODULE_REF(basic_user_manager) {
    return std::shared_ptr<core::IModule>(new basic::UserManagerModule);
}

}  // namespace asty
