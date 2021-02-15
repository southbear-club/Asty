/**
 * @file init_global_source.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#define ASTY_MODULE_NAME "entry"

#include "init_global_source.hpp"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <gflags/gflags.h>
#include "common/common.hpp"
#include "common/utils/asty_coredump.hpp"
#include "configure.hpp"
#include "core/asty_config.hpp"
#include "core/asty_log.hpp"
#include "core/asty_log_in.hpp"
#include "log_cfg.hpp"

namespace asty {

namespace entry {

/**
 * @brief 进程重复运行检测，只允许single模式
 *
 */
class AloneProccess {
private:
    /**
     * @brief Construct a new Alone Proccess object
     *
     * @param pid_file pid文件，用于检测
     */
    AloneProccess(const char *pid_file) : pid_(pid_file), fd_(-1) {
        fd_ = open(pid_file, O_RDWR | O_CREAT, 0666);
        if (fd_ < 0) {
            throw std::runtime_error(std::string("can not open pid file : ") +
                                     pid_file);
        }
    }
    ~AloneProccess() {
        if (fd_ > 0) {
            close(fd_);
        }
    }

public:
    static bool check(const char *pid_file) {
        static AloneProccess alone(pid_file);
        return alone.IsAlone();
    }

    /**
     * @brief 文件锁定
     *
     * @return true 锁定成功
     * @return false 锁定失败
     */
    bool LockFile(void) {
        struct flock fl;

        fl.l_type = F_WRLCK;  // 锁定文件，锁定失败则是已经运行了一个
        fl.l_start = 0;
        fl.l_whence = SEEK_SET;
        fl.l_len = 0;

        return fcntl(fd_, F_SETLK, &fl) == 0;
    }

    /**
     * @brief 进程single检测
     *
     * @return true single
     * @return false 非single
     */
    bool IsAlone(void) {
        if (!LockFile()) {
            if (errno == EACCES || errno == EAGAIN) {
                close(fd_);
                fd_ = -1;
                std::cout << "proccessing is running!" << std::endl;
                return false;
            }
            std::cout << "can't lock " << pid_
                      << ", reason :" << strerror(errno) << std::endl;
        }

        char buf[16] = {'\0'};

        if (ftruncate(fd_, 0) != 0) {
            std::cout << "ftruncate " << pid_ << ", reason :" << strerror(errno)
                      << std::endl;
            return false;
        }

        sprintf(buf, "%ld", (long)getpid());
        return write(fd_, buf, strlen(buf) + 1) > 0;
    }

    DISALLOW_COPY_AND_ASSIGN(AloneProccess);

private:
    std::string pid_;
    int fd_;
};

void init_global_source(int argc, char **argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);

    if (!AloneProccess::check(PID_FILE)) {
        exit(-1);
    }

#ifdef DEBUG
    // debug模式设置coredump，1Gb coredump文件大小限制
    // if (!utils::setup_coredump(ASTY_COREDUMP_PATH, 1024 * 1024 * 1024)) {
    //     std::cout << "setup coredump error." << std::endl;
    //     exit(-1);
    // }
#endif

    // 初始化日志
    core::AstyLog::init(argv[0], ASTY_LOG_PATH);
#ifdef DEBUG
    core::AstyLog::set_single_module_lvl(ASTY_MODULE_NAME, core::ASTY_INFO);
#endif

    // 加载配置参数
    core::AstyParameter::init(ASTY_CONFIG_FILENAME);

    // 配置模块日志等级
    config_log_lvl();
}

}  // namespace entry

}  // namespace asty
