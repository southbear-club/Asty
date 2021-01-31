/**
 * @file asty_info.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>

namespace asty {

namespace core {

/**
 * @brief 应用信息
 * 
 */
typedef struct {
    std::string type;           ///< 类型
    std::string edition;        ///< 发布类型
    std::string version;        ///< 应用版本号
    std::string identifier;     ///< 唯一标识
    std::string compile_time;   ///< 发布时间
    std::string firmware_code;  ///< 固件代码
} app_info;

// TODO:cpu信息
// TODO:操作系统信息
// TODO:内存信息
// TODO:磁盘信息
// TODO:文件系统信息

/**
 * @brief Get the application info object
 * 
 * @return app_info 
 */
app_info get_application_info(void);

}

}