/**
 * @file http_user.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "http_auth.hpp"

namespace asty {

namespace op_http_srv {

class HttpUserPasswordImpl : public HttpUserPassword {
public:
    virtual ~HttpUserPasswordImpl() {}
    virtual std::string password(const std::string &username) override;
};

}  // namespace op_http_srv

}  // namespace asty