/**
 * @file http_server.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#define ASTY_MODULE_NAME "http server"
#include "http_server.hpp"
#include "http_server.pb.h"
#include "http_midware.hpp"
#include "http_router.hpp"
#include "http_uri_list.hpp"
#include "core/asty_log.hpp"
#include "core/asty_config.hpp"
#include <thread>
#include <string>
#include <brpc/server.h>
#include <brpc/restful.h>

namespace asty {

namespace op_http_srv {

class HttpServiceImpl : public HttpService {
public:
    HttpServiceImpl() {
        midwares_ = get_midware_list();
        router_.add(get_http_uri_list());
    };
    virtual ~HttpServiceImpl() {
    };
    void open_api(google::protobuf::RpcController* cntl_base,
              const HttpRequest*,
              HttpResponse*,
              google::protobuf::Closure* done) {

        brpc::ClosureGuard done_guard(done);
        
        brpc::Controller* cntl =
            static_cast<brpc::Controller*>(cntl_base);

        // TODO:过滤用户注册uri

        // 中间件
        for (auto &item : midwares_) {
            if (item && item->en_) {
                auto mid_ret = item->midware(cntl);
                if (mid_ret != 0) {
                    ASTY_LOG(WARNING) << "midware : " << item->name_ << " filter error : " << mid_ret << "\n";
                    return;
                }
            }
        }

        // 路由
        router_.router(cntl);
    }

    void admin_api(google::protobuf::RpcController* cntl_base,
              const HttpRequest*,
              HttpResponse*,
              google::protobuf::Closure* done) {

        brpc::ClosureGuard done_guard(done);
        
        brpc::Controller* cntl =
            static_cast<brpc::Controller*>(cntl_base);
        // Fill response.
        cntl->http_response().set_content_type("text/plain");
        butil::IOBufBuilder os;
        os << "queries:";
        for (brpc::URI::QueryIterator it = cntl->http_request().uri().QueryBegin();
                it != cntl->http_request().uri().QueryEnd(); ++it) {
            os << ' ' << it->first << '=' << it->second;
        }
        os << "\nbody: " << cntl->request_attachment() << '\n';
        os.move_to(cntl->response_attachment());
    }
private:
    std::vector<IHttpMidware*> midwares_;
    HttpRouter router_;
};

class HttpServerImpl {
public:
    HttpServerImpl() {
        server_.AddService(&service_, brpc::SERVER_DOESNT_OWN_SERVICE,
                            "/astyop/open-api/*  => open_api,"
                            "/astyop/admin-api/* => admin_api",
                            "/20210212 => open_api");
        run_ = false;
    }

    ~HttpServerImpl() {
        stop();
    }

    bool start(const std::string &ip, int port, int internal_port) {
        if (run_) {
            return true;
        }

        run_ = true;

        brpc::ServerOptions options;

        options.idle_timeout_sec = -1;
        options.internal_port = internal_port;
        // options.auth = &auth_;
        // options.mutable_ssl_options()->default_cert.certificate = FLAGS_certificate;
        // options.mutable_ssl_options()->default_cert.private_key = FLAGS_private_key;
        // options.mutable_ssl_options()->ciphers = FLAGS_ciphers;

        if (server_.Start((ip + ":" + std::to_string(port)).c_str(), &options) != 0) {
            run_ = false;
            ASTY_LOG(ERROR) << "Fail to start HttpServer\n";
            return false;
        }

        http_t_ = std::thread([&] {
            server_.RunUntilAskedToQuit();
        });

        return true;
    }

    void stop() {
        if (!run_) {
            return;
        }

        server_.Stop(0);
        http_t_.join();
        run_ = false;
    }

private:
    brpc::Server server_;
    HttpServiceImpl service_;
    // HttpAuthImpl auth_;
    std::thread http_t_;
    bool run_;
};

static const core::module_base_info_t in_module_info {
    "http server",
    "open api of http",
    "1.0.0",
    true,
    "",
    core::E_MODULE_TYPE_ACCESS,
    core::E_MODULE_GROUP_OPENAPI,
    core::E_MODULE_PER_USER,
};

HttpServerOpenApiModule::HttpServerOpenApiModule() : core::IModule(in_module_info), http_srv_impl_(nullptr) {
}

HttpServerOpenApiModule::~HttpServerOpenApiModule() {

}

bool HttpServerOpenApiModule::init(void *param) {
    http_srv_impl_ = new HttpServerImpl();
    return true;
}

bool HttpServerOpenApiModule::start(void *param) {
    if (!http_srv_impl_) {
        return false;
    }

    auto http_cfg = GET_PARAM_ONCE(["module"]["open api"]["http server"]);
    http_srv_impl_->start("0.0.0.0", http_cfg["net"]["listen port"], http_cfg["net"]["internal port"]);
    return true;
}

bool HttpServerOpenApiModule::stop(void *param) {
    if (!http_srv_impl_) {
        return false;
    }

    http_srv_impl_->stop();
    
    return true;
}

bool HttpServerOpenApiModule::exit(void *param) {
    if (http_srv_impl_) {
        delete http_srv_impl_;
        http_srv_impl_ = nullptr;
    }
    return true;
}

}  // namespace op_http_srv

DEFINE_ASTY_MODULE_REF(openapi_http_server) {
    static bool init = false;
    if (init) {
        return nullptr;
    }

    init = true;
    std::shared_ptr<core::IModule> module(new op_http_srv::HttpServerOpenApiModule);

    return module;
}

}  // namespace asty
