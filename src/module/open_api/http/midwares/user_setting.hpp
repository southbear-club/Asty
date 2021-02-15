/**
 * @file user_setting.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "../http_midware.hpp"

namespace asty {

namespace op_http_srv {

// user register
// user setting
// user unregister

class HttpUserMidware : public IHttpMidware {
public:
    HttpUserMidware(const std::string &name, bool en);
    virtual ~HttpUserMidware();
    virtual int midware(http_midware_ctrl *ctrl) override;

private:
    int user_register(http_midware_ctrl *ctrl);
    int user_setting(http_midware_ctrl *ctrl);
    int user_unregister(http_midware_ctrl *ctrl);
};

}  // namespace op_http_srv

}  // namespace asty