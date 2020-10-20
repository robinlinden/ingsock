#include "ingsock.h"

#include <catch2/catch.hpp>

#include <string>
#include <sstream>

using namespace ingsock;

TEST_CASE("IpAddrV4::localhost") {
    REQUIRE(IpAddrV4::localhost().ip == IpAddrV4(127, 0, 0, 1).ip);
}

TEST_CASE("IpAddrV4::any") {
    REQUIRE(IpAddrV4::any().ip == IpAddrV4(0, 0, 0, 0).ip);
}

TEST_CASE("IpAddrV4::ostream") {
    using namespace std::literals;
    std::stringstream ss;
    ss << IpAddrV4::localhost();
    REQUIRE(ss.str() == "127.0.0.1"s);
}
