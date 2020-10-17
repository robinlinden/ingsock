#ifndef INGSOCK_H
#define INGSOCK_H

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
};

// SocketAddr
struct SocketAddrV4 {
    IpAddrV4 ip;
    uint16_t port;
};

struct SocketAddr {
    constexpr SocketAddr(SocketAddrV4 v) : is_ipv4{true}, v4{v} {}

    bool is_ipv4;
    SocketAddrV4 v4;
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
