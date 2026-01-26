#include "ing/socket.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

using namespace ing;

TEST_CASE("IpAddrV6::parse") {
    using namespace std::literals;
    REQUIRE(IpAddrV6::localhost().ip == IpAddrV6::parse("::1"s).ip);
    REQUIRE(IpAddrV6::any().ip == IpAddrV6::parse("::"s).ip);
}

TEST_CASE("IpAddrV6::localhost") {
    std::array<std::byte, 16> localhost{};
    localhost[15] = static_cast<std::byte>(1);
    REQUIRE(IpAddrV6::localhost().ip == localhost);
}

TEST_CASE("IpAddrV6::any") { REQUIRE(IpAddrV6::any().ip == std::array<std::byte, 16>{}); }

TEST_CASE("IpAddrV6::ostream") {
    using namespace std::literals;
    std::stringstream ss;
    ss << IpAddrV6::localhost();
    REQUIRE(ss.str() == "::1"s);
}
