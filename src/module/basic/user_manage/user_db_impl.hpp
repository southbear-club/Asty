/**
 * @file user_db_impl.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <memory>
#include "common/functions/database/database.hpp"
#include "user_db.hpp"

namespace asty {

namespace basic {

class UserDbImpl : public IUserDb {
public:
    UserDbImpl(mongocxx::client *db);
    virtual ~UserDbImpl();

public:
    virtual int insert(const user_base_info_t &usr) override;
    virtual int remove(const std::string &name) override;
    virtual int query(const std::string &name, user_base_info_t &user) override;
    virtual int set_permission(const std::string &name,
                               int permission) override;
    virtual int set_phone(const std::string &name,
                          const std::string &phone) override;
    virtual int set_email(const std::string &name,
                          const std::string &email) override;
    virtual int set_sex(const std::string &name, uint8_t sex) override;
    virtual int set_age(const std::string &name, uint32_t age) override;
    virtual int set_addr(const std::string &name,
                         const std::string &adr) override;
    virtual int set_desc(const std::string &name,
                         const std::string &desc) override;

    virtual std::list<user_base_info_t> query_by_permission(
        int permission) override;
    virtual std::list<user_base_info_t> query_by_sex(uint8_t sex) override;
    virtual std::list<user_base_info_t> query_by_age(uint32_t age) override;
    virtual std::list<user_base_info_t> query_by_addr(
        const std::string &addr) override;
    virtual std::list<user_base_info_t> query_by_birthday(
        const std::string &birthday) override;
    virtual std::list<user_base_info_t> query_by_status(uint8_t st) override;

private:
    mongocxx::client *db_;
};

}  // namespace basic

}  // namespace asty
