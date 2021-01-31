/**
 * @file asty_md5.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <stddef.h>
#include <stdint.h>

namespace asty {

namespace utils {

typedef struct {
    uint64_t bytes;
    uint32_t a, b, c, d;
    uint8_t buffer[64];
} md5_t;

void md5_init(md5_t *ctx);
void md5_update(md5_t *ctx, const void *data, size_t size);
void md5_final(uint8_t result[16], md5_t *ctx);

}  // namespace utils

}  // namespace asty
