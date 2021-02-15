/**
 * @file http_router.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <brpc/restful.h>
#include <brpc/server.h>
#include <functional>
#include <list>
#include <string>
#include <set>

namespace asty {

namespace op_http_srv {

using http_route_ctrl = brpc::Controller;

struct HttpNode {
    std::string uri;     ///< TODO:更丰富的uri支持
    std::set<brpc::HttpMethod> methods;
    std::function<int(http_route_ctrl*)> proc;
};

class HttpRouter {
public:
    HttpRouter();
    HttpRouter(const std::initializer_list<HttpNode> &li);
    ~HttpRouter();

    int router(http_route_ctrl *cntl);
    void add(const HttpNode &node);
    void add(const std::list<HttpNode> &nodes);

private:
    std::list<HttpNode> nodes_;
};

}  // namespace op_http_srv

}  // namespace asty
