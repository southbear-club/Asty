/**
 * @file asty_system_call.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <string>
#include <vector>

namespace asty {

namespace utils {

int popen(const char *cmd, std::vector<std::string> &resvec);

}  // namespace utils

}  // namespace asty
