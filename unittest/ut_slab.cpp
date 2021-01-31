/**
 * @file ut_slab.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "common/utils/asty_lock.hpp"
#include "common/utils/asty_slab.hpp"

using namespace asty;

TEST(UTILS, UtilsSlab) {
    utils::ILock *lck = new utils::CppMtxLock;
    char *p = new char[4 * 1024 *1024]; // 4M
    utils::slab_stat_t st;
    utils::MemorySlab slab(p, 4 * 1024 * 1024, lck);

    int i;

    slab.stat(st);
    LOG(INFO) << "###################################################################################\n";

    void *n;
    for (i  = 0; i < 1000000; i++) {
        n = slab.alloc(128 + i);
        EXPECT_NE(nullptr, n);
        slab.free(n);
    }

    slab.stat(st);

    LOG(INFO) << "###################################################################################\n";

    for (i = 0; i < 2500; i++) {
        n = slab.alloc(30 + i);
        EXPECT_NE(nullptr, n);
        if (i % 3 == 0) {
            slab.free(n);
        }
    }

    slab.stat(st);

    LOG(INFO) << "###################################################################################\n";

    for (i = 0; i < 2500; i++) {
        n = slab.alloc(8);
        EXPECT_NE(nullptr, n);
        if (i % 3 == 0) {
            slab.free(n);
        }
    }

    slab.alloc(4 * 1024);
    slab.alloc(16 * 1024);

    slab.stat(st);

    delete [] p;
}