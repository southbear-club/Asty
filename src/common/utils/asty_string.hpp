/**
 * @file asty_string.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <string>

namespace asty {

namespace utils {

// 邮箱校验
bool email_match(const std::string &email);
// 手机号码校验
bool zh_cellphone_number_match(const std::string &number);
// 身份证校验
bool id_card_match(const std::string &number);
// ipv4 校验
bool ipv4_match(const std::string &ip);
// ipv6 校验
bool ipv6_match(const std::string &ip);

}  // namespace utils

}  // namespace asty
