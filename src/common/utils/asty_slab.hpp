/**
 * @file asty_slab.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <stdint.h>
#include "asty_lock.hpp"

namespace asty {

namespace utils {

typedef struct slab_pool_s slab_pool_t;
class MemorySlabImpl;

typedef struct {
    size_t pool_size, used_size, used_pct;
    size_t pages, free_page;
    size_t p_small, p_exact, p_big, p_page; /* 四种slab占用的page数 */
    size_t b_small, b_exact, b_big, b_page; /* 四种slab占用的byte数 */
    size_t max_free_pages;                  /* 最大的连续可用page数 */
} slab_stat_t;

class MemorySlab {
public:
    MemorySlab(void *addr, size_t len, ILock *mem_lock,
               uint8_t min_size_shift = 3);
    ~MemorySlab();

    void *alloc(size_t size);
    void free(void *p);
    void stat(slab_stat_t &st);

private:
    MemorySlabImpl *impl_;
};

}  // namespace utils

}  // namespace asty
