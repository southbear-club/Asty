include "asty_gw_msg.thrift"

namespace cpp asty_gw_sdk

service AstyGwPlatformSever {
    bool ping(),
    asty_gw_msg.AstyGwMsgResponse device_online(1: asty_gw_msg.AstyGwMsgRequest request),
    asty_gw_msg.AstyGwMsgResponse device_register(1: asty_gw_msg.AstyGwMsgRequest request),
    asty_gw_msg.AstyGwMsgResponse get_mq_host(1: asty_gw_msg.AstyGwMsgRequest request),
    asty_gw_msg.AstyGwMsgResponse request(1: asty_gw_msg.AstyGwMsgRequest request)
}