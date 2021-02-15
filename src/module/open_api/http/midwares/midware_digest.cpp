/**
 * @file midware_digest.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "midware_digest.hpp"

namespace asty {

namespace op_http_srv {

HttpAuthMidware::HttpAuthMidware(const std::string &name, bool en)
    : IHttpMidware(name, en), auth_(nullptr) {
    http_digest_conf_t digest_conf = {
        "astrolrovers@outlook.com", 60, 10, 300, 20, 300, 5,
    };

    auth_ = new HttpDigestAuth(digest_conf, &http_user_);
}

HttpAuthMidware::~HttpAuthMidware() { delete auth_; }

int HttpAuthMidware::midware(http_midware_ctrl *cntl) {
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> header_ret;
    for (auto b = cntl->http_request().HeaderBegin();
         b != cntl->http_request().HeaderEnd(); b++) {
        headers[b->first] = b->second;
    }

    auto digest_ret = auth_->process(
        brpc::HttpMethod2Str(cntl->http_request().method()),
        cntl->http_request().uri().path(), headers, header_ret,
        std::string(butil::ip2str(cntl->remote_side().ip).c_str()) + ":" +
            std::to_string(cntl->remote_side().port));

    for (auto &item : header_ret) {
        cntl->http_response().SetHeader(item.first, item.second);
    }

    cntl->http_response().set_status_code(digest_ret);

    return digest_ret == 200 ? 0 : -1;
}

}  // namespace op_http_srv

}  // namespace asty