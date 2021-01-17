include "asty_gw_msg.thrift"
namespace cpp asty_gw_sdk

service AstyGwDeviceSever {

    asty_gw_msg.AstyGwMsgResponse request(1: asty_gw_msg.AstyGwMsgRequest request),

    asty_gw_msg.AstyGwMsgResponse user_bind(1: asty_gw_msg.AstyGwMsgRequest request)
}