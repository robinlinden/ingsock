#include "ingsock.h"

#include <catch2/catch.hpp>

#include <string>
#include <sstream>

using namespace ingsock;

TEST_CASE("IpAddrV6::localhost") {
    std::array<std::byte, 16> localhost{};
    localhost[15] = static_cast<std::byte>(1);
    REQUIRE(IpAddrV6::localhost().ip == localhost);
}

TEST_CASE("IpAddrV6::any") {
    REQUIRE(IpAddrV6::any().ip == std::array<std::byte, 16>{});
}

TEST_CASE("IpAddrV6::ostream") {
    using namespace std::literals;
    std::stringstream ss;
    ss << IpAddrV6::localhost();
    REQUIRE(ss.str() == "::1"s);
}
