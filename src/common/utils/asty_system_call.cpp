/**
 * @file asty_system_call.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "asty_system_call.hpp"
#include <stdio.h>
#include <string.h>

namespace asty {

namespace utils {

// execute shell
// command//执行一个shell命令，输出结果逐行存储在resvec中，并返回行数
int popen(const char *cmd, std::vector<std::string> &resvec) {
    resvec.clear();

    FILE *pp = ::popen(cmd, "r");  //建立管道

    if (!pp) {
        return -1;
    }

    char tmp[1024];  //设置一个合适的长度，以存储每一行输出
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        if (tmp[strlen(tmp) - 1] == '\n') {
            tmp[strlen(tmp) - 1] = '\0';  //去除换行符
        }
        resvec.push_back(tmp);
    }

    pclose(pp);  //关闭管道
    return resvec.size();
}

}  // namespace utils

}  // namespace asty
