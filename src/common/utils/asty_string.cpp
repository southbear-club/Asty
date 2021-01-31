/**
 * @file asty_string.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "asty_string.hpp"
#include <regex>

namespace asty {

namespace utils {

static bool _match(const std::string &str, const std::string &re_str) {
    std::cmatch cm;
    std::regex re(re_str.c_str());

    return std::regex_match(str.c_str(), cm, re);
}

bool email_match(const std::string &email) {
    return _match(
        email,
        "^([A-Za-z0-9_\\-\\.])+\\@([A-Za-z0-9_\\-\\.])+\\.([A-Za-z]{2,4})$");
}

bool id_card_match(const std::string &number) {
    return _match(number, "(^\\d{15}$)|(^\\d{17}([0-9]|X)$)");
}

bool zh_cellphone_number_match(const std::string &number) {
    return _match(number, "^1[3456789]\\d{9}$");
}

bool ipv4_match(const std::string &ip) {
    return _match(ip + ".",
                  "^((\\d|[1-9]\\d|1\\d\\d|2([0-4]\\d|5[0-5]))\\.){4}$");
}

bool ipv6_match(const std::string &ip) {
    return _match(ip + ":", "^(([\\da-fA-F]{1,4}):){8}$");
}

}  // namespace utils

}  // namespace asty
