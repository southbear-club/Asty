/**
 * @file asty_config.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "asty_config.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace asty {

namespace core {

AstyParameter::AstyParameter(const std::string &path) : path_(path) {
    try {
        std::ifstream f(path);
        f >> param_;
    } catch (const json_t::parse_error &e) {
        throw std::invalid_argument(e.what());
    }
}

void AstyParameter::init(const std::string &path) {
    AstyParameter::get_instance(path);
}

AstyParameter &AstyParameter::get_instance(const std::string &path) {
    static AstyParameter param(path);
    return param;
}

json_t &AstyParameter::parameter_ref(void) { return param_; }

bool AstyParameter::dump(void) {
    std::ofstream f(path_);
    f << std::setw(4) << param_ << std::endl;

    return true;
}

bool AstyParameter::dump(const json_t &param) {
    param_ = param;
    return dump();
}

}  // namespace core

}  // namespace asty
