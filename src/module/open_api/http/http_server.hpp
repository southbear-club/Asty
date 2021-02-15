/**
 * @file http_server.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-07
 * 
 * @copyright Copyright (c) 2021
 * 
 * @note api管理：https://yapi.baidu.com/
 * 
 */
#pragma once
#include "core/module.hpp"

namespace asty {

namespace op_http_srv {

class HttpServerImpl;

class HttpServerOpenApiModule : public core::IModule {
public:
    HttpServerOpenApiModule();
    virtual ~HttpServerOpenApiModule();

    virtual bool init(void *param) override;

    virtual bool start(void *param) override;

    virtual bool stop(void *param) override;

    virtual bool exit(void *param) override;

    // todo:路由注册
    static int add_router(void) {
        return 0;
    }

private:
    HttpServerImpl *http_srv_impl_;
};

}  // namespace op_http_srv

DEFINE_ASTY_MODULE_REF(openapi_http_server);

}  // namespace asty
