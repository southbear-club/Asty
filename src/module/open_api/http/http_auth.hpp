/**
 * @file http_auth.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-13
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <list>
#include <map>
#include <mutex>
#include <vector>
#include <string>

namespace asty {

namespace op_http_srv {

/**
 * @brief 配置
 *
 */
typedef struct {
    std::string realm;
    time_t timeout;       ///< 60s
    time_t expires;       ///< 10s
    time_t drop_time;     ///< 300s
    int replays;          ///< 20
    time_t evasion_time;  ///< 300s
    int maxtries;         ///< 5
} http_digest_conf_t;

/**
 * @brief 验证信息
 *
 */
typedef struct {
    std::string auth_scheme;
    std::string username;
    std::string realm;
    std::string nonce;
    std::string nc;
    std::string uri;
    std::string qop;
    std::string cnonce;
    std::string response;
    std::string opaque;
    std::string stale;
} http_auth_digest_cred_t;

/**
 * @brief nonce值
 *
 */
typedef struct {
    uint32_t rnd;
    time_t t;
} http_auth_digest_nonce_t;

/**
 * @brief 节点
 *
 */
typedef struct {
    time_t expires;
    time_t drop_time;
    std::vector<int> nc;
} http_auth_digest_node_t;

// evasion entries
typedef struct {
    time_t drop_time;
    int failcnt;
    std::string src_addr;
} http_auth_digest_ev_node_t;

/**
 * @brief 获取用户密码
 *
 */
class HttpUserPassword {
public:
    virtual ~HttpUserPassword() {}
    virtual std::string password(const std::string &username) = 0;
};

class HttpDigestAuth {
public:
    HttpDigestAuth(const http_digest_conf_t &conf, HttpUserPassword *user_pass);

    int process(const std::string &method, const std::string &uri,
                const std::map<std::string, std::string> &headers,
                std::map<std::string, std::string> &header_ret,
                const std::string &src_addr);

private:
    std::string md5hex(const void *data, size_t len);
    std::string hex_dump(const unsigned char *src, size_t len);
    bool auth_digest_evading(const std::string &src_addr);
    bool auth_digest_check_credentials(
        const std::map<std::string, std::string> &headers,
        http_auth_digest_cred_t &cred);
    http_auth_digest_nonce_t auth_digest_next_nonce(void);
    int auth_digest_challenge(
        std::map<std::string, std::string> &header_ret, bool stale);
    int auth_digest_verify_user(const std::string &method,
                                const std::string &uri,
                                std::map<std::string, std::string> &header_ret,
                                http_auth_digest_cred_t &cred);
    void auth_digest_evasion_tracking(const std::string &src_addr, int status);
    void cleanup(void);

private:
    http_digest_conf_t conf_;
    HttpUserPassword *user_pass_;
    std::mutex mtx_;
    std::map<std::string, http_auth_digest_node_t> node_map_;
    std::map<std::string, http_auth_digest_ev_node_t> ev_node_map_;
};

}  // namespace op_http_srv

}  // namespace asty
