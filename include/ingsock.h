#ifndef INGSOCK_H
#define INGSOCK_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>

namespace ingsock {

// IpAddr
struct IpAddrV4 {
    constexpr IpAddrV4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) :
            ip{static_cast<uint32_t>(a | b << 8 | c << 16 | d << 24)} {}
    std::uint32_t ip;

    static constexpr IpAddrV4 localhost() { return IpAddrV4{127, 0, 0, 1}; }
    static constexpr IpAddrV4 any() { return IpAddrV4{0, 0, 0, 0}; }
};

struct IpAddrV6 {
    explicit constexpr IpAddrV6(std::array<std::byte, 16> ip_) : ip{ip_} {}
    std::array<std::byte, 16> ip;

    static constexpr std::array<std::byte, 16> localhost() {
        std::array<std::byte, 16> ip{};
        ip[15] = static_cast<std::byte>(1);
        return ip;
    }

    static constexpr std::array<std::byte, 16> any() {
        return std::array<std::byte, 16>{};
    }
};

// SocketAddr
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

// Socket
enum class Domain {
    ipv4,
    ipv6,
};

enum class Type {
    stream,
    dgram,
};

enum class Protocol {
    tcp,
    udp,
};

class Socket {
public:
    Socket(Domain d, Type t, Protocol p);
    explicit Socket(int socket);

    bool connect(SocketAddr addr);
    bool bind(SocketAddr addr);
    bool listen(int backlog);
    Socket accept();

    int recv(std::byte *buf, int len);
    int send(const std::byte *buf, int len);

private:
    // Technically sockets are 64-bit on Windows x64, but
    // things like OpenSSL receive it as an int in their
    // API, so this is unlikely to ever break.
    int socket_;
};

int last_error();

}

#endif
