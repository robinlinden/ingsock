#include "ingsock.h"

#include <catch2/catch.hpp>

using namespace ingsock;

TEST_CASE("Socket::Socket(&&)") {
    Socket s1{Domain::ipv4, Type::dgram, Protocol::udp};
    Socket s2{std::move(s1)};
    REQUIRE(s1.close() == -1); // NOLINT(bugprone-use-after-move)
    REQUIRE(s2.close() == 0);
}

TEST_CASE("Socket::operator=(Socket &&)") {
    Socket s1{Domain::ipv4, Type::dgram, Protocol::udp};
    Socket s2 = std::move(s1);
    REQUIRE(s1.close() == -1); // NOLINT(bugprone-use-after-move)
    REQUIRE(s2.close() == 0);
}
