#ifndef INGSOCK_SOCKET_ADDR_H
#define INGSOCK_SOCKET_ADDR_H

#include "ingsock/ip_addr.h"

#include <cstdint>

namespace ingsock {

struct SocketAddrV4 {
    IpAddrV4 ip;
    uint16_t port;
};

struct SocketAddrV6 {
    IpAddrV6 ip;
    uint16_t port;
};

struct SocketAddr {
    constexpr SocketAddr(SocketAddrV4 v) : is_ipv4{true}, v4{v} {}
    constexpr SocketAddr(SocketAddrV6 v) : is_ipv4{false}, v6{v} {}

    bool is_ipv4;
    union {
        SocketAddrV4 v4;
        SocketAddrV6 v6;
    };
};

} // namespace ingsock

#endif
