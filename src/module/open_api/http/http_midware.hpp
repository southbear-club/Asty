/**
 * @file http_midware.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <brpc/server.h>
#include <brpc/restful.h>

namespace asty
{

namespace op_http_srv
{

using http_midware_ctrl = brpc::Controller;

class IHttpMidware {
public:
    IHttpMidware(const std::string &name, bool en)
        : name_(name), en_(en) {}
    virtual ~IHttpMidware() {}

    virtual int midware(http_midware_ctrl *ctrl) = 0;

    std::string name_;
    bool en_;
};

void insert_midware(IHttpMidware *midware);
std::vector<IHttpMidware*> get_midware_list(void);

} // namespace op_http_srv

} // namespace asty
