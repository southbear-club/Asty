/**
 * @file http_auth.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-13
 *
 * @copyright Copyright (c) 2021
 *
 */
#define ASTY_MODULE_NAME "http server"
#include "http_auth.hpp"
#include "core/asty_log.hpp"
#include <cctype>
#include <algorithm>
#include <stdlib.h>
#include <butil/base64.h>
#include <butil/sha1.h>
#include <butil/strings/string_number_conversions.h>
#include <butil/strings/string_split.h>
#include <butil/strings/string_util.h>
#include <sys/time.h>
#include "common/utils/asty_md5.hpp"

namespace asty {

namespace op_http_srv {

#define LF     (unsigned char) '\n'
#define CR     (unsigned char) '\r'
#define CRLF   "\r\n"

HttpDigestAuth::HttpDigestAuth(const http_digest_conf_t &conf,
                               HttpUserPassword *user_pass)
    : conf_(conf), user_pass_(user_pass) {
    srand(time(nullptr));
}

int HttpDigestAuth::process(const std::string &method, const std::string &uri,
                            const std::map<std::string, std::string> &headers,
                            std::map<std::string, std::string> &header_ret,
                            const std::string &src_addr) {
    ASTY_LOG(INFO) << "method : " << method << "\nuri : " << uri << "\naddr : " << src_addr << "\n";
    for (auto &item : headers) {
        ASTY_LOG(INFO) << item.first << " : " << item.second << "\n";
    }

    std::unique_lock<std::mutex> lck(mtx_);
    // 验证超时检测
    if (!auth_digest_evading(src_addr)) {
        return 401;
    }

    // igest记录
    http_auth_digest_cred_t cred;
    // 检查是否是第一次请求
    if (!auth_digest_check_credentials(headers, cred)) {
        // 首次请求则进行握手
        return auth_digest_challenge(header_ret, false);
    }

    auto ret = auth_digest_verify_user(method, uri, header_ret, cred);
    if (200 == ret) {
        auth_digest_evasion_tracking(src_addr, 1);
    } else {
        auth_digest_evasion_tracking(src_addr, 0);
        ret = auth_digest_challenge(header_ret, true);
    }

    cleanup();

    return ret;
}

std::string HttpDigestAuth::md5hex(const void *data, size_t len) {
    uint8_t md5[16] = "";
    utils::md5_t mobj;
    utils::md5_init(&mobj);
    utils::md5_update(&mobj, (const unsigned char *)data, len);
    utils::md5_final(md5, &mobj);

    return hex_dump(md5, 16);
}

std::string HttpDigestAuth::hex_dump(const unsigned char *src, size_t len) {
    static char hex[] = "0123456789abcdef";
    std::string dst;

    while (len--) {
        dst.push_back(hex[*src >> 4]);
        dst.push_back(hex[*src++ & 0xf]);
    }

    return dst;
}

bool HttpDigestAuth::auth_digest_evading(const std::string &src_addr) {
    auto node = ev_node_map_.find(src_addr);
    if (node != ev_node_map_.end()) {
        ASTY_LOG(INFO) << "find src addr : " << src_addr << "\n";
        if (node->second.failcnt >= conf_.maxtries &&
            time(nullptr) < node->second.drop_time) {
            ASTY_LOG(INFO) << "fail cnt max\n";
            return false;
        }
    }

    return true;
}

bool HttpDigestAuth::auth_digest_check_credentials(
    const std::map<std::string, std::string> &headers,
    http_auth_digest_cred_t &cred) {
    auto auth_key = headers.find("Authorization");

    if (auth_key == headers.end()) {
        ASTY_LOG(INFO) << "not find key Authorization\n";
        return false;
    }

    std::string auth_value = auth_key->second;

    /*
        token          = 1*<any CHAR except CTLs or separators>
        separators     = "(" | ")" | "<" | ">" | "@"
                        | "," | ";" | ":" | "\" | <">
                        | "/" | "[" | "]" | "?" | "="
                        | "{" | "}" | SP | HT
    */
    static uint32_t token_char[]{
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */

        /* ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
        0x03ff6cf8, /* 0000 0011 1111 1111  0110 1100 1111 1000 */

        /* _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
        0xc7fffffe, /* 1100 0111 1111 1111  1111 1111 1111 1110 */

        /*  ~}| {zyx wvut srqp  onml kjih gfed cba` */
        0x57ffffff, /* 0101 0111 1111 1111  1111 1111 1111 1111 */

        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
    };

    uint32_t in_value;
    unsigned char ch, *p, *last, *start = 0, *end;
    std::string name, value;
    int comma_cnt = 0, quoted_pair_cnt = 0;

    // 解析验证信息
    enum {
        sw_start = 0,
        sw_scheme,
        sw_scheme_end,
        sw_lws_start,
        sw_lws,
        sw_param_name_start,
        sw_param_name,
        sw_param_value_start,
        sw_param_value,
        sw_param_quoted_value,
        sw_param_end,
        sw_error,
    } state;

    state = sw_start;
    p = (unsigned char *)auth_value.data();
    last = (unsigned char *)auth_value.data() + auth_value.size();

    ch = *p++;

    while (p <= last) {
        switch (state) {
            default:
            case sw_error:
                return false;
            case sw_start:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                if (ch == CR || ch == LF || ch == ' ' || ch == '\t') {
                    ch = *p++;
                } else if (token_char[ch >> 5] & (1 << (ch & 0x1f))) {
                    start = p - 1;
                    state = sw_scheme;
                } else {
                    state = sw_error;
                }
                break;

            case sw_scheme:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                if (token_char[ch >> 5] & (1 << (ch & 0x1f))) {
                    ch = *p++;
                } else if (ch == ' ') {
                    end = p - 1;
                    state = sw_scheme_end;
                    cred.auth_scheme =
                        std::string((const char *)start, end - start);

                    // ASTY_LOG(INFO) << "auth scheme : " << cred.auth_scheme << " \n";
                    if (cred.auth_scheme != "Digest") {
                        state = sw_error;
                    }
                } else {
                    state = sw_error;
                }
                break;
            case sw_scheme_end:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                if (ch == ' ') {
                    ch = *p++;
                } else {
                    state = sw_param_name_start;
                }
                break;
            case sw_lws_start:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                comma_cnt = 0;
                state = sw_lws;
                // fall through
            case sw_lws:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                if (comma_cnt > 0 &&
                    (token_char[ch >> 5] & (1 << (ch & 0x1f)))) {
                    state = sw_param_name_start;
                } else if (ch == ',') {
                    comma_cnt++;
                    ch = *p++;
                } else if (ch == CR || ch == LF || ch == ' ' || ch == '\t') {
                    ch = *p++;
                } else {
                    state = sw_error;
                }
                break;
            case sw_param_name_start:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                if (token_char[ch >> 5] & (1 << (ch & 0x1f))) {
                    start = p - 1;
                    state = sw_param_name;
                    ch = *p++;
                } else {
                    state = sw_error;
                }
                break;
            case sw_param_name:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                if (token_char[ch >> 5] & (1 << (ch & 0x1f))) {
                    ch = *p++;
                } else if (ch == '=') {
                    end = p - 1;
                    state = sw_param_value_start;
                    name = std::string((const char *)start, end - start);
                    // ASTY_LOG(INFO) << "name : " << name << " \n";

                    ch = *p++;
                } else {
                    state = sw_error;
                }
                break;
            case sw_param_value_start:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                if (token_char[ch >> 5] & (1 << (ch & 0x1f))) {
                    start = p - 1;
                    state = sw_param_value;
                    ch = *p++;
                } else if (ch == '\"') {
                    start = p;
                    quoted_pair_cnt = 0;
                    state = sw_param_quoted_value;
                    ch = *p++;
                } else {
                    state = sw_error;
                }
                break;
            case sw_param_value:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                in_value = token_char[ch >> 5] & (1 << (ch & 0x1f));
                if (in_value) {
                    ch = *p++;
                }

                if (!in_value || p > last) {
                    end = p - 1;
                    value = std::string((const char *)start, end - start);
                    // ASTY_LOG(INFO) << "value : " << value << " \n";
                    state = sw_param_end;
                    goto param_end;
                }
                break;
            case sw_param_quoted_value:
                // ASTY_LOG(INFO) << "ch : " << ch << "\n";
                if (ch < 0x20 || ch == 0x7f) {
                    state = sw_error;
                } else if (ch == '\\' && *p <= 0x7f) {
                    quoted_pair_cnt++;
                    ch = *(p += 2);
                } else if (ch == '\"') {
                    end = p - 1;
                    ch = *p++;
                    value = std::string((const char *)start,
                                        end - start - quoted_pair_cnt);
                    if (quoted_pair_cnt > 0) {
                        value.clear();
                        for (unsigned char *s = start; s < end; s++) {
                            ch = *s;
                            if (ch == '\\') {
                                s++;
                                if (s < end) {
                                    value.push_back(ch);
                                }
                                continue;
                            }
                            value.push_back(ch);
                        }
                    }
                    // ASTY_LOG(INFO) << "value : " << value << " \n";
                    state = sw_param_end;
                    goto param_end;
                } else {
                    ch = *p++;
                }
                break;

            param_end:
            case sw_param_end:
                if (name == "username") {
                    cred.username = value;
                } else if (name == "qop") {
                    cred.qop = value;
                } else if (name == "realm") {
                    cred.realm = value;
                } else if (name == "nonce") {
                    cred.nonce = value;
                } else if (name == "nc") {
                    cred.nc = value;
                } else if (name == "uri") {
                    cred.uri = value;
                } else if (name == "cnonce") {
                    cred.cnonce = value;
                } else if (name == "response") {
                    cred.response = value;
                } else if (name == "opaque") {
                    cred.opaque = value;
                }
                state = sw_lws_start;
                break;
        }
    }

    ASTY_LOG(INFO) << "username : " << cred.username << "\nqop : " << cred.qop << "\nrealm : " << cred.realm
                    << "\nnonce : " << cred.nonce << "\nnc : " << cred.nc << "\nuri : " << cred.uri
                    << "\ncnonce : " << cred.cnonce << "\nresponse : " << cred.response << "\n";

    if (state != sw_lws_start && state != sw_lws) {
        return false;
    }

    if (cred.username.empty() || cred.qop.empty() || cred.realm.empty() ||
        cred.nonce.empty() || cred.nc.empty() || cred.uri.empty() ||
        cred.cnonce.empty() || cred.response.empty() ||
        cred.nonce.length() != 16) {
        return false;
    }
    return true;
}

http_auth_digest_nonce_t HttpDigestAuth::auth_digest_next_nonce(void) {
    http_auth_digest_nonce_t nonce;
    while (1) {
        nonce.t = time(nullptr);
        nonce.rnd = rand();
        std::string key =
            std::to_string(nonce.t) + ":" + std::to_string(nonce.rnd);
        std::hash<std::string> hash_key;
        std::stringstream s;
        s << hash_key(key);
        std::string key_str = s.str();
        auto item = node_map_.find(key_str);

        ASTY_LOG(INFO) << "node map key : " << key_str << "\n";

        // 找到了说明已经存在了
        if (item != node_map_.end()) {
            ASTY_LOG(INFO) << "find node map key : " << key_str << "\n";
            continue;
        }

        http_auth_digest_node_t node;
        node.expires = nonce.t + conf_.timeout;
        node.drop_time = nonce.t + conf_.drop_time;
        node.nc = std::vector<int>(conf_.replays, 0);

        node_map_[key_str] = node;

        ASTY_LOG(INFO) << "new nonce, rnd : " << nonce.rnd << " t : " << nonce.t << "\n";

        return nonce;
    }
}

int HttpDigestAuth::auth_digest_challenge(
    std::map<std::string, std::string> &header_ret, bool stale) {
    std::string challenge = "Digest algorithm=\"MD5\", qop=\"auth\", realm=\"";
    challenge += conf_.realm + "\", nonce=\"";
    char tmp[17];
    auto nonce = auth_digest_next_nonce();
    // 前8字节为rnd，后8字节为t
    sprintf(tmp, "%08x%08lx", nonce.rnd, nonce.t);
    challenge += tmp;

    if (stale) {
        challenge += "\", stale=\"true\"";
    } else {
        challenge += "\"";
    }

    ASTY_LOG(INFO) << "challenge : " << challenge << "\n";

    header_ret["WWW-Authenticate"] = challenge;

    return 401;
}

int HttpDigestAuth::auth_digest_verify_user(
    const std::string &method, const std::string &uri,
    std::map<std::string, std::string> &header_ret,
    http_auth_digest_cred_t &cred) {
    if (!user_pass_) {
        return 500;
    }

    std::string password = user_pass_->password(cred.username);

    if (password.empty()) {
        return 500;
    }

    //  the hashing scheme:
    //    digest:
    //    MD5(MD5(username:realm:password):nonce:nc:cnonce:qop:MD5(method:uri))
    //                ^- HA1                                           ^- HA2
    //    verify: fields->response ==
    //    MD5($hashed_pw:nonce:nc:cnonce:qop:MD5(method:uri))

    // ha1 was precalculated and saved to the passwd file:
    // md5(username:realm:password)

    std::string hash1 = cred.username + ":" + conf_.realm + ":" + password;
    hash1 = md5hex(hash1.data(), hash1.size());
    std::string hash2str = method + ":" + uri;
    std::string hash2 = md5hex(hash2str.data(), hash2str.size());

    std::string digest_key = hash1 + ":" + cred.nonce + ":" + cred.nc + ":" +
                             cred.cnonce + ":" + cred.qop + ":" + hash2;
    digest_key = md5hex(digest_key.data(), digest_key.size());

    ASTY_LOG(INFO) << "digest key : " << digest_key << "\nresponse : " << cred.response << "\n";

    // 密码验证
    if (digest_key != cred.response) {
        return 500;
    }

    // 检查nonce和nc
    http_auth_digest_nonce_t nonce;
    int nc = 0;
    butil::StringPiece rndp(cred.nonce.substr(0, 8));
    butil::StringPiece tp(cred.nonce.substr(8));
    butil::StringPiece np(cred.nc);
    butil::HexStringToUInt(rndp, &nonce.rnd);
    butil::HexStringToInt64(tp, &nonce.t);
    butil::HexStringToInt(np, &nc);

    ASTY_LOG(INFO) << "rnd : " << nonce.rnd << " t : " << nonce.t << " nc : " << nc;

    // 重新分配的
    if (nc < 0 || nc >= conf_.replays) {
        cred.stale = true;
        return 500;
    }

    std::string key = std::to_string(nonce.t) + ":" + std::to_string(nonce.rnd);
    std::hash<std::string> hash_key;
    std::stringstream s;
    s << hash_key(key);
    std::string key_str = s.str();
    auto item = node_map_.find(key_str);

    ASTY_LOG(INFO) << "find item key str : " << key_str << "\n";

    // 未找到记录
    if (item != node_map_.end()) {
        // 记录超时
        if (item->second.expires <= time(nullptr)) {
            ASTY_LOG(INFO) << "key str : " << key_str << " timeout\n";
            cred.stale = true;
            goto invalid;
        }

        if (nc < 0 || nc >= (int)item->second.nc.size()) {
            ASTY_LOG(INFO) << "nc : " << nc << " invalid\n";
            goto invalid;
        }

        // 该nc已经被占用
        if (item->second.nc[nc]) {
            ASTY_LOG(INFO) << "nc : " << nc << " invalid\n";
            goto invalid;
        }

        // 第一次请求
        if (item->second.nc[0]) {
            item->second.nc[0] = 1;
            item->second.expires = time(nullptr) + conf_.expires;
            item->second.drop_time = time(nullptr) + conf_.drop_time;
        }

        // 标记占用
        item->second.nc[nc] = 1;

        hash2str = ":";
        hash2str += uri;

        hash2 = md5hex(hash2str.data(), hash2str.size());

        digest_key = hash1 + ":" + cred.nonce + ":" + cred.nc + ":" +
                     cred.cnonce + ":" + cred.qop + ":" + hash2;
        digest_key = md5hex(digest_key.data(), digest_key.size());

        std::string hkey = "qop=\"auth\", rspauth=\"";
        hkey += digest_key + "\", " + "cnonce=\"" + cred.cnonce + "\", " +
                "nc=" + cred.nc;
        header_ret["Authentication-Info"] = hkey;

        return 200;
    }
    ASTY_LOG(INFO) << "not find item key str : " << key_str << "\n";

invalid:
    return 500;
}

void HttpDigestAuth::auth_digest_evasion_tracking(const std::string &src_addr,
                                                  int status) {
    auto item = ev_node_map_.find(src_addr);
    http_auth_digest_ev_node_t node;

    if (item == ev_node_map_.end()) {
        if (status == 1) {
            return;
        }
        node.src_addr = src_addr;
        ev_node_map_[src_addr] = node;
    }

    if (status == 1) {
        ev_node_map_[src_addr].failcnt = 0;
        ev_node_map_[src_addr].drop_time = time(nullptr);
    } else {
        if (time(nullptr) > ev_node_map_[src_addr].drop_time) {
            ev_node_map_[src_addr].failcnt = 0;
        } else {
            ev_node_map_[src_addr].failcnt += 1;
        }
        ev_node_map_[src_addr].drop_time = time(nullptr) + conf_.evasion_time;
    }
}

void HttpDigestAuth::cleanup(void) {
    time_t now = time(nullptr);
    std::list<std::string> clean_list;

    for (auto &item : node_map_) {
        if (item.second.drop_time <= now) {
            clean_list.push_back(item.first);
        }
    }

    for (auto &item : clean_list) {
        node_map_.erase(item);
    }

    clean_list.clear();

    for (auto &item : ev_node_map_) {
        if (item.second.drop_time <= now) {
            clean_list.push_back(item.first);
        }
    }

    for (auto &item : clean_list) {
        ev_node_map_.erase(item);
    }
}

}  // namespace op_http_srv

}  // namespace asty
