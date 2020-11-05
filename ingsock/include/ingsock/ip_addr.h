#ifndef INGSOCK_IP_ADDR_V4_H
#define INGSOCK_IP_ADDR_V4_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>
#include <variant>

namespace ingsock {

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

} // namespace ingsock

#endif
