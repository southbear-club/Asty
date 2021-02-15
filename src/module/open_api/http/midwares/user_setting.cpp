/**
 * @file user_setting.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "user_setting.hpp"
#include "basic/user_manage/user_manager_module.hpp"

namespace asty {

namespace op_http_srv {

HttpUserMidware::HttpUserMidware(const std::string &name, bool en)
    : IHttpMidware(name, en) {

}

HttpUserMidware::~HttpUserMidware() {

}

int HttpUserMidware::midware(http_midware_ctrl *ctrl) {
    return 0;
}

int HttpUserMidware::user_register(http_midware_ctrl *ctrl) {
    auto user_module = (basic::UserManagerModule *)(ASTY_MODULE_REF(basic_user_manager).get());

    basic::IUserManager *user_manage = user_module->user_manager();

    return 0;
}

int HttpUserMidware::user_setting(http_midware_ctrl *ctrl) {
    return 0;
}

int HttpUserMidware::user_unregister(http_midware_ctrl *ctrl) {
    return 0;
}

}  // namespace op_http_srv

}  // namespace asty