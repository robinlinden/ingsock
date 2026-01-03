#include "ing/socket.h"

#include <catch2/catch_test_macros.hpp>

using namespace ing;

TEST_CASE("Socket::Socket(&&)") {
    Socket s1{Domain::ipv4, Type::udp};
    Socket s2{std::move(s1)};
    REQUIRE(s1.close() == -1); // NOLINT(bugprone-use-after-move)
    REQUIRE(s2.close() == 0);
}

TEST_CASE("Socket::operator=(Socket &&)") {
    Socket s1{Domain::ipv4, Type::udp};
    Socket s2 = std::move(s1);
    REQUIRE(s1.close() == -1); // NOLINT(bugprone-use-after-move)
    REQUIRE(s2.close() == 0);
}

TEST_CASE("resolve") {
    const auto ips = resolve("localhost");
    REQUIRE(!ips.empty());
    if (std::holds_alternative<IpAddrV4>(ips.at(0))) {
        REQUIRE(std::get<IpAddrV4>(ips.at(0)).ip == IpAddrV4::localhost().ip);
    } else {
        REQUIRE(std::get<IpAddrV6>(ips.at(0)).ip == IpAddrV6::localhost().ip);
    }
}
