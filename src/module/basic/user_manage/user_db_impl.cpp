/**
 * @file user_db_impl.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "user_db_impl.hpp"
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

namespace asty {

namespace basic {

UserDbImpl::UserDbImpl(mongocxx::client *db) : db_(db) {
    // mongocxx::database db_ = (*db)["astyCloudPlatform"];
    // auto cursor = db_["astyCloudPlatform"].find({});
    // for (auto&& doc : cursor) {
    //     std::cout << bsoncxx::to_json(doc) << std::endl;
    // }
}

UserDbImpl::~UserDbImpl() {}

int UserDbImpl::insert(const user_base_info_t &usr) { return 0; }

int UserDbImpl::remove(const std::string &name) { return 0; }

int UserDbImpl::query(const std::string &name, user_base_info_t &user) {
    return 0;
}

int UserDbImpl::set_permission(const std::string &name, int permission) {
    return 0;
}

int UserDbImpl::set_phone(const std::string &name, const std::string &phone) {
    return 0;
}

int UserDbImpl::set_email(const std::string &name, const std::string &email) {
    return 0;
}

int UserDbImpl::set_sex(const std::string &name, uint8_t sex) { return 0; }

int UserDbImpl::set_age(const std::string &name, uint32_t age) { return 0; }

int UserDbImpl::set_addr(const std::string &name, const std::string &adr) {
    return 0;
}
int UserDbImpl::set_desc(const std::string &name, const std::string &desc) {
    return 0;
}

std::list<user_base_info_t> UserDbImpl::query_by_permission(int permission) {
    std::list<user_base_info_t> users;
    return users;
}

std::list<user_base_info_t> UserDbImpl::query_by_sex(uint8_t sex) {
    std::list<user_base_info_t> users;
    return users;
}

std::list<user_base_info_t> UserDbImpl::query_by_age(uint32_t age) {
    std::list<user_base_info_t> users;
    return users;
}

std::list<user_base_info_t> UserDbImpl::query_by_addr(const std::string &addr) {
    std::list<user_base_info_t> users;
    return users;
}

std::list<user_base_info_t> UserDbImpl::query_by_birthday(
    const std::string &birthday) {
    std::list<user_base_info_t> users;
    return users;
}

std::list<user_base_info_t> UserDbImpl::query_by_status(uint8_t st) {
    std::list<user_base_info_t> users;
    return users;
}

}  // namespace basic

}  // namespace asty
