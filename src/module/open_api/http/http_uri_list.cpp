/**
 * @file http_uri_list.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "http_uri_list.hpp"
#include "services/new_year.hpp"

namespace asty {

namespace op_http_srv {

static std::list<HttpNode> http_node_list {
    { "/astyop/open-api/newyear/2021", {brpc::HTTP_METHOD_GET}, newyear_show },
};

std::list<HttpNode> &get_http_uri_list(void) {
    return http_node_list;
}

void http_uri_add(const HttpNode &uri_node) {
    http_node_list.push_back(uri_node);
}

void http_uri_add(const std::list<HttpNode> &uri_nodes) {
    for (auto &item : uri_nodes) {
        http_node_list.push_back(item);
    }
}

} // namespace op_http_srv

} // namespace asty
