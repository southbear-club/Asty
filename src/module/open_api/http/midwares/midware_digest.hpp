/**
 * @file midware_digest.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "../http_midware.hpp"
#include "../http_auth.hpp"
#include "../http_user.hpp"

namespace asty {

namespace op_http_srv {

class HttpAuthMidware : public IHttpMidware {
public:
    HttpAuthMidware(const std::string &name, bool en);
    virtual ~HttpAuthMidware();
    virtual int midware(http_midware_ctrl *ctrl) override;

private:
    HttpDigestAuth *auth_;
    HttpUserPasswordImpl http_user_;
};

}  // namespace op_http_srv

}  // namespace asty