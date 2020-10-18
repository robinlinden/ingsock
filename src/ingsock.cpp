#include "ingsock.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#define INVALID_SOCKET (-1)
#endif

// TODO(robinlinden): Error handling.

namespace ingsock {
namespace {
#ifdef _WIN32
struct WinsockInitializer {
    WinsockInitializer() {
        WSADATA wsa_data;
        WSAStartup(MAKEWORD(2, 2), &wsa_data);
    }
    ~WinsockInitializer() {
        WSACleanup();
    }
};
[[maybe_unused]] WinsockInitializer ws = WinsockInitializer();
#endif

constexpr int into_os(Domain d) {
    switch (d) {
        case Domain::ipv4:
            return AF_INET;
        case Domain::ipv6:
            return AF_INET6;
    }
    std::abort();
}

constexpr int into_os(Type t) {
    switch (t) {
        case Type::stream:
            return SOCK_STREAM;
        case Type::dgram:
            return SOCK_DGRAM;
    }
    std::abort();
}

constexpr int into_os(Protocol p) {
    switch (p) {
        case Protocol::tcp:
            return IPPROTO_TCP;
        case Protocol::udp:
            return IPPROTO_UDP;
    }
    std::abort();
}

std::pair<struct sockaddr_storage, std::size_t> into_os(SocketAddr addr) {
    struct sockaddr_storage s = {0};
    if (addr.is_ipv4) {
        auto *a = reinterpret_cast<sockaddr_in *>(&s);
        a->sin_family = AF_INET;
        a->sin_addr.s_addr = addr.v4.ip.ip;
        a->sin_port = addr.v4.port;
        return {s, sizeof(*a)};
    } else {
        auto *a = reinterpret_cast<sockaddr_in6 *>(&s);
        a->sin6_family = AF_INET6;
        std::memcpy(a->sin6_addr.s6_addr, addr.v6.ip.ip.data(), addr.v6.ip.ip.size());
        a->sin6_port = addr.v6.port;
        return {s, sizeof(*a)};
    }
}

} // namespace

std::ostream &operator<<(std::ostream &os, IpAddrV4 ip) {
    std::string str{};
    str.resize(16);
    struct in_addr addr = {0};
    addr.s_addr = ip.ip;
    if (inet_ntop(AF_INET, &addr, str.data(), str.size()) == nullptr) {
        throw std::runtime_error("bad ip address in << for ipv4");
    }

    os << str;
    return os;
}
std::ostream &operator<<(std::ostream &os, IpAddrV6 ip) {
    std::string str{};
    str.resize(46);
    if (inet_ntop(AF_INET, &ip.ip, str.data(), str.size()) == nullptr) {
        throw std::runtime_error("bad ip address in << for ipv6");
    }

    os << str;
    return os;
}

Socket::Socket(Domain d, Type t, Protocol p) :
        socket_{static_cast<int>(::socket(into_os(d), into_os(t), into_os(p)))} {}

Socket::Socket(int socket) : socket_{socket} {}

bool Socket::connect(const SocketAddr addr) {
    const auto [a, size] = into_os(addr);
    return ::connect(socket_, reinterpret_cast<const struct sockaddr *>(&a), size) == 0;
};

bool Socket::bind(const SocketAddr addr) {
    const auto [a, size] = into_os(addr);
    return ::bind(socket_, reinterpret_cast<const struct sockaddr *>(&a), size) == 0;
}

bool Socket::listen(const int backlog) {
    return ::listen(socket_, backlog) == 0;
}

Socket Socket::accept() {
    auto socket{::accept(socket_, nullptr, nullptr)};
    assert(socket != INVALID_SOCKET);
    return Socket{static_cast<int>(socket)};
}

int Socket::recv(std::byte *buf, int len) {
    return ::recv(socket_, reinterpret_cast<char *>(buf), len, 0);
}

int Socket::send(const std::byte *buf, int len) {
    return ::send(socket_, reinterpret_cast<const char *>(buf), len, 0);
}

int last_error() {
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

} // namespace ingsock
