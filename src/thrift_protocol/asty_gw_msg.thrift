namespace cpp asty_gw_sdk

enum AstyGwDomainE {
    GW_DOMAIN_MICRO_KERNEL = 0,
    GW_DOMAIN_BASIC = 1,
    GW_DOMAIN_ALARM = 2,
    GW_DOMAIN_DEVICE = 3,
    GW_DOMAIN_MEDIA = 4,
    GW_DOMAIN_SPEC = 5,
    GW_DOMAIN_TRANSPORT = 6
}

struct AstyGwMsgResponse {
    1: string result,
    2: binary data,
}

struct AstyGwMsgRequest {
    1: string header,
    2: binary data,
}
