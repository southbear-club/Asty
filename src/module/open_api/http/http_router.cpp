/**
 * @file http_router.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "http_router.hpp"

namespace asty {

namespace op_http_srv {

HttpRouter::HttpRouter() {

}

HttpRouter::HttpRouter(const std::initializer_list<HttpNode> &li) : nodes_(li) {

}

HttpRouter::~HttpRouter() {}

int HttpRouter::router(http_route_ctrl *cntl) {
    for (auto &node : nodes_) {
        if (node.uri == cntl->http_request().uri().path()) {
            // 服务器错误
            if (!node.proc) {
                cntl->http_response().set_status_code(500);
                return -1;
            }

            // 方法不支持
            if (0 == node.methods.count(cntl->http_request().method())) {
                cntl->http_response().set_status_code(405);
                return -1;
            }

            return node.proc(cntl);
        }
    }
    
    cntl->http_response().set_status_code(404);
    return -1;
}

void HttpRouter::add(const HttpNode &node) {
    nodes_.push_back(node);
}

void HttpRouter::add(const std::list<HttpNode> &nodes) {
    for (auto &item : nodes) {
        nodes_.push_back(item);
    }
}

}  // namespace op_http_srv

}  // namespace asty
