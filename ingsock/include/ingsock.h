#ifndef INGSOCK_H
#define INGSOCK_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace ingsock {

// IpAddr
struct IpAddrV4 {
    static IpAddrV4 parse(const std::string &ip);

    constexpr IpAddrV4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) :
            ip{static_cast<uint32_t>(a | b << 8 | c << 16 | d << 24)} {}
    explicit constexpr IpAddrV4(std::uint32_t ip_) : ip{ip_} {}
    std::uint32_t ip;

    static constexpr IpAddrV4 localhost() { return IpAddrV4{127, 0, 0, 1}; }
    static constexpr IpAddrV4 any() { return IpAddrV4{0, 0, 0, 0}; }
};
std::ostream &operator<<(std::ostream &os, IpAddrV4 ip);

struct IpAddrV6 {
    static IpAddrV6 parse(const std::string &ip);

    constexpr IpAddrV6() : ip{} {}
    explicit constexpr IpAddrV6(std::array<std::byte, 16> ip_) : ip{ip_} {}
    std::array<std::byte, 16> ip;

    static constexpr IpAddrV6 localhost() {
        std::array<std::byte, 16> ip{};
        ip[15] = static_cast<std::byte>(1);
        return IpAddrV6{ip};
    }

    static constexpr IpAddrV6 any() {
        return IpAddrV6{std::array<std::byte, 16>{}};
    }
};
std::ostream &operator<<(std::ostream &os, IpAddrV6 ip);

using IpAddr = std::variant<IpAddrV4, IpAddrV6>;

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
    tcp,
    udp,
};

enum class Shutdown {
    receive,
    send,
    both,
};

class Socket {
public:
    Socket(Domain d, Type t) noexcept;
    explicit Socket(int socket) noexcept;

    Socket(const Socket &) = delete;
    Socket &operator=(const Socket &) = delete;

    Socket(Socket &&) noexcept;
    Socket &operator=(Socket &&) noexcept;

    ~Socket() noexcept;

    bool connect(SocketAddr addr) noexcept;
    bool bind(SocketAddr addr) noexcept;
    bool listen(int backlog) noexcept;
    Socket accept() noexcept;

    int shutdown(Shutdown what) noexcept;
    int close() noexcept;

    int recv(std::byte *buf, int len) noexcept;
    int send(const std::byte *buf, int len) noexcept;

    template<class T>
    int recv(T *buf) noexcept(noexcept(buf->data() && buf->size())) {
        return recv(reinterpret_cast<std::byte *>(buf->data()), buf->size());
    }

    template<class T>
    int send(const T &buf) noexcept(noexcept(buf.data() && buf.size())) {
        return send(reinterpret_cast<const std::byte *>(buf.data()), buf.size());
    }

private:
    // Technically sockets are 64-bit on Windows x64, but
    // things like OpenSSL receive it as an int in their
    // API, so this is unlikely to ever break.
    int socket_;
};

int last_error() noexcept;
std::vector<IpAddr> resolve(const char *name);

}

#endif
