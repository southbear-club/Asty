/**
 * @file version.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <string.h>
#include "version.hpp"

namespace asty
{

namespace core
{

/**
 * @brief 应用版本
 * 
 * @return const std::string& 
 */
const std::string asty_version(void) {
#ifndef SOFT_VERSION
    #define SOFT_VERSION "0.0.0"
#endif

    return SOFT_VERSION;
}

/**
 * @brief 应用编译时间
 * 
 * @return const std::string& 
 */
const std::string asty_compile_time(void) {
#ifndef APP_COMPILE_TIME
    #define APP_COMPILE_TIME "Monday 2021-01-01 00:00:00 +0800"
#endif
    return APP_COMPILE_TIME;
}

/**
 * @brief 识别码
 * 
 * @return const std::string& 
 */
const std::string asty_app_identifier(void) {
#ifndef APP_UUID
    #define APP_UUID "00000000-0000-0000-0000-000000000000"
#endif

    return APP_UUID;
}

} // namespace core

} // namespace asty
