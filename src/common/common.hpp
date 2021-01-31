/**
 * @file common.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <stdint.h>

namespace asty
{

#define asty_align(d, a) (((d) + (a - 1)) & ~(a - 1))
#define asty_align_ptr(p, a) \
    (uint8_t *)(((uintptr_t)(p) + ((uintptr_t)a - 1)) & ~((uintptr_t)a - 1))

#ifndef DISALLOW_COPY_AND_ASSIGN

#define DISALLOW_COPY_AND_ASSIGN(Type) \
    Type(const Type&) = delete; \
    void operator=(const Type&) = delete

#endif

} // namespace asty
