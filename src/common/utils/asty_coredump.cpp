/**
 * @file asty_coredump.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "asty_coredump.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

namespace asty {

namespace utils {

static const char *const core_format = "core-%e-%p-%t";

bool setup_coredump(const char *path_dir, size_t core_size) {
    struct rlimit rlmt;
    char core_path[1024];

    if (NULL == path_dir) return false;

    if (getrlimit(RLIMIT_CORE, &rlmt) < 0) {
        return false;
    }

    rlmt.rlim_cur = (rlim_t)core_size;
    rlmt.rlim_max = (rlim_t)core_size;

    if (setrlimit(RLIMIT_CORE, &rlmt) < 0) {
        return false;
    }

    if (path_dir[strlen(path_dir) - 1] != '/') {
        sprintf(core_path, "echo %s/%s > /proc/sys/kernel/core_pattern",
                path_dir, core_format);
    } else {
        sprintf(core_path, "echo %s%s > /proc/sys/kernel/core_pattern",
                path_dir, core_format);
    }

    sprintf(core_path, "echo %s/%s > /proc/sys/kernel/core_pattern", path_dir,
            core_format);
    if (system(core_path) != 0) {
        return false;
    }

    if (system("echo 1 > /proc/sys/kernel/core_uses_pid") != 0) {
        return false;
    }

    return true;
}

}  // namespace utils

}  // namespace asty
