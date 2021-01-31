/**
 * @file ut_main.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    // 输出到标准输出而不是文件
    FLAGS_logtostderr = true;
    // 除了输出到文件，也输出到终端
    FLAGS_alsologtostderr = true;
    // 打印色彩
    FLAGS_colorlogtostderr = true;
    FLAGS_minloglevel = google::GLOG_INFO;

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}