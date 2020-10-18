#include "ingsock.h"

#include <array>
#include <cstddef>
#include <iostream>

using namespace ingsock;

int main(int, char **) {
    Socket s{Domain::ipv6, Type::stream, Protocol::tcp};

    std::array<std::byte, 16> ip{};
    ip[15] = static_cast<std::byte>(1);
    if (!s.connect(SocketAddrV6{IpAddrV6{ip}, 22222})) {
        const int err{last_error()};
        std::cerr << "Failed to connect to server: " << err << std::endl;
        return 1;
    }

    std::array<std::byte, 1024> recv_buf{};
    while (s.recv(recv_buf.data(), recv_buf.size()) > 0) {
        std::cout << reinterpret_cast<const char*>(recv_buf.data()) << std::endl;
        recv_buf.fill(static_cast<std::byte>(0));
    }

    return 0;
}
