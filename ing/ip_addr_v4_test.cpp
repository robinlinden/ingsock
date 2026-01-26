#include "ing/socket.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

using namespace ing;

TEST_CASE("IpAddrV4::parse") {
    using namespace std::literals;
    REQUIRE(IpAddrV4::localhost().ip == IpAddrV4::parse("127.0.0.1"s).ip);
    REQUIRE(IpAddrV4(10, 65, 100, 93).ip == IpAddrV4::parse("10.65.100.93"s).ip);
    REQUIRE(IpAddrV4(0, 0, 0, 0).ip == IpAddrV4::parse("0.0.0.0"s).ip);
}

TEST_CASE("IpAddrV4::localhost") { REQUIRE(IpAddrV4::localhost().ip == IpAddrV4(127, 0, 0, 1).ip); }

TEST_CASE("IpAddrV4::any") { REQUIRE(IpAddrV4::any().ip == IpAddrV4(0, 0, 0, 0).ip); }

TEST_CASE("IpAddrV4::ostream") {
    using namespace std::literals;
    std::stringstream ss;
    ss << IpAddrV4::localhost();
    REQUIRE(ss.str() == "127.0.0.1"s);
}
