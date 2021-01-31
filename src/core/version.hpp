/**
 * @file version.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <string>

namespace asty
{

namespace core
{

/**
 * @brief 应用版本
 * 
 * @return const std::string& 
 */
const std::string asty_version(void);

/**
 * @brief 应用编译时间
 * 
 * @return const std::string& 
 */
const std::string asty_compile_time(void);

/**
 * @brief app识别码，该程序从编译好后的唯一性
 * @details uuid-v4
 * 
 * @return const std::string& 
 */
const std::string asty_app_identifier(void);

} // namespace core

} // namespace asty
