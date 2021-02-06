/**
 * @file user_manage.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <memory>
#include "user_db.hpp"

namespace asty {

namespace basic {

class IUserManager {
public:
    IUserManager() {}
    virtual ~IUserManager() {}

    virtual std::shared_ptr<IUserDb> user_db(void) = 0;
};

}  // namespace basic

}  // namespace asty
