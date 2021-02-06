/**
 * @file user_manager_module.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include "core/module.hpp"
#include "user_manage.hpp"

namespace asty {

namespace basic {

class UserManagerModule : public core::IModule {
public:
    UserManagerModule();
    virtual ~UserManagerModule();

    virtual bool init(void *db) override;

    virtual bool start(void *param) override;

    virtual bool stop(void *param) override;

    virtual bool exit(void *param) override;

    IUserManager *user_manager(void);

private:
    IUserManager *user_ma_;
};

}  // namespace basic

DEFINE_ASTY_MODULE_REF(basic_user_manager);

}  // namespace asty
