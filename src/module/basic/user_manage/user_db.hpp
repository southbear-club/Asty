/**
 * @file user_db.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "user_info.hpp"
#include <list>

namespace asty
{
    
namespace basic
{

class IUserDb {
public:
    IUserDb() {}
    virtual ~IUserDb() {}

public:
    virtual int insert(const user_base_info_t &usr) = 0;
    virtual int remove(const std::string &name) = 0;
    virtual int query(const std::string &name, user_base_info_t &user) = 0;
    virtual int set_permission(const std::string &name, int permission) = 0;
    virtual int set_phone(const std::string &name, const std::string &phone) = 0;
    virtual int set_email(const std::string &name, const std::string &email) = 0;
    virtual int set_sex(const std::string &name, uint8_t sex) = 0;
    virtual int set_age(const std::string &name, uint32_t age) = 0;
    virtual int set_addr(const std::string &name, const std::string &adr) = 0;
    virtual int set_desc(const std::string &name, const std::string &desc) = 0;

    virtual std::list<user_base_info_t> query_by_permission(int permission) = 0;
    virtual std::list<user_base_info_t> query_by_sex(uint8_t sex) = 0;
    virtual std::list<user_base_info_t> query_by_age(uint32_t age) = 0;
    virtual std::list<user_base_info_t> query_by_addr(const std::string &addr) = 0;
    virtual std::list<user_base_info_t> query_by_birthday(const std::string &birthday) = 0;
    virtual std::list<user_base_info_t> query_by_status(uint8_t st) = 0;
};
    
} // namespace basic

} // namespace asty
