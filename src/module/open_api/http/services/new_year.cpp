/**
 * @file new_year.cpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief 
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "new_year.hpp"

namespace asty {

namespace op_http_srv {

int newyear_show(http_route_ctrl *cntl) {
    butil::IOBufBuilder os;

    cntl->http_response().set_content_type("application/json");

    os << "{\"data\": \"happy Newyear\", \"status\": \"ok\"}";
    os.move_to(cntl->response_attachment());
    cntl->http_response().set_status_code(200);

    return 0;
}

}  // namespace op_http_srv

}  // namespace asty
