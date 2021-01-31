/**
 * @file asty_coredump.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <stddef.h>

namespace asty
{

namespace utils
{

/**
 * @brief Set the up coredump object
 *
 * @param path_dir : coredump生成路径
 * @param core_size : 文件大小
 * @return true : 设置成功
 * @return false : 设置失败
 */
bool setup_coredump(const char *path_dir, size_t core_size);

} // namespace utils

} // namespace asty
