/**
 * @file device_info.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>
#include <stdint.h>

namespace asty
{

namespace basic
{

typedef struct {
    std::string name;       ///< 设备名称
    std::string nikname;    ///< 设备名称
    std::string type;       ///< 设备类型
    std::string subtype;    ///< 子类型
    std::string serial_no;  ///< 设备序列号
    std::string firmware_code;  ///< 固件代码
    std::string device_id;  ///< 设备id，用于设备的第二次上线，唯一标识一个设备，用户绑定后该id不能丢失
    // std::string operation_code; ///< 报备码，设备报备后分配的代码，用户设备能否可以分配device_id，表明为合法设备，临时请求一个吧
    std::string user;       ///< 关联账户
    std::string version;    ///< 当前版本
    uint8_t device_status;  ///< 设备状态
    std::string zone;       ///< 接入区域(域名，环境)
    std::string res;        ///< 扩展
    std::string capa;       ///< 设备能力集
} devce_base_info_t;

} // namespace basic

} // namespace asty
