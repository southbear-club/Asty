/**
 * @file http_midware.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "http_midware.hpp"
#include "midwares/midware_digest.hpp"

namespace asty
{

namespace op_http_srv
{

static std::vector<IHttpMidware*> midwarelist {
    new HttpAuthMidware("digest auth", true),
};

void insert_midware(IHttpMidware *midware) {
    midwarelist.push_back(midware);
}

std::vector<IHttpMidware*> get_midware_list(void) {
    return midwarelist;
}

} // namespace op_http_srv

} // namespace asty
