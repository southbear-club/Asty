/**
 * @file http_uri_list.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "http_router.hpp"

namespace asty {

namespace op_http_srv {

std::list<HttpNode> &get_http_uri_list(void);
void http_uri_add(const HttpNode &uri_node);
void http_uri_add(const std::list<HttpNode> &uri_nodes);

} // namespace op_http_srv

} // namespace asty
