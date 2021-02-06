/**
 * @file user_manage_impl.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "user_manage.hpp"
namespace asty {

namespace basic {

class UserManager : public IUserManager {
public:
    UserManager(std::shared_ptr<IUserDb> userdb);
    virtual ~UserManager();

    virtual std::shared_ptr<IUserDb> user_db(void) override;

private:
    std::shared_ptr<IUserDb> userdb_;
};

}  // namespace basic

}  // namespace asty
