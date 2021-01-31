/**
 * @file main.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "main.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include "core/datatype.hpp"
#include "core/version.hpp"
#include "configure.hpp"
#include "init_global_source.hpp"
#include "module_list.hpp"

using namespace asty;

static void print_app_description(void) {
    std::cout << std::setiosflags(std::ios::left);

    std::cout << std::setw(30) << "[application name "
              << "] ==> "
              << "apsd[asty platform server deamon]" << std::endl;
    std::cout << std::setw(30) << "[compile time "
              << "] ==> "
              << core::asty_compile_time() << std::endl;
    std::cout << std::setw(30) << "[application version "
              << "] ==> "
              << core::asty_version() << std::endl;
#ifdef DEBUG
    std::cout << std::setw(30) << "[application edition "
              << "] ==> "
              << "debug" << std::endl;
#else
    std::cout << std::setw(30) << "[application edition "
              << "] ==> "
              << "release" << std::endl;
#endif
    std::cout << std::setw(30) << "[application identifier "
              << "] ==> "
              << core::asty_app_identifier() << std::endl;
    std::cout << std::setw(30) << "[aplication author "
              << "] ==> "
              << "wotsen(astralrovers#outlook.com)" << std::endl;
    std::cout << std::setw(30) << "[copyright "
              << "] ==> "
              << "MIT" << std::endl;

    std::cout.unsetf(std::ios::left);
}

int main(int argc, char **argv) {
    // 打印应用基本信息
    print_app_description();

    // 初始化全局资源：程序运行时，信号处理，coredump, 配置参数，日志
    entry::init_global_source(argc, argv);

    // 启动模块
    entry::setup_module();

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
