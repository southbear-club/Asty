/**
 * @file user_manage_impl.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "user_manage_impl.hpp"
namespace asty {

namespace basic {

UserManager::UserManager(std::shared_ptr<IUserDb> userdb) : userdb_(userdb) {

}

UserManager::~UserManager() {

}

std::shared_ptr<IUserDb> UserManager::user_db(void) {
    return userdb_;
}

}  // namespace basic

}  // namespace asty
