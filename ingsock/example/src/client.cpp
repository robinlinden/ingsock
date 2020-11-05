#include "ingsock.h"

#include <array>
#include <cstddef>
#include <iostream>

using namespace ingsock;

int main(int, char **) {
    Socket s{Domain::ipv4, Type::stream, Protocol::tcp};

    if (!s.connect(SocketAddrV4{IpAddrV4::localhost(), 22222})) {
        const int err{last_error()};
        std::cerr << "Failed to connect to server: " << err << std::endl;
        return 1;
    }

    std::array<std::byte, 1024> recv_buf{};
    while (s.recv(&recv_buf) > 0) {
        std::cout << reinterpret_cast<const char*>(recv_buf.data()) << std::endl;
        recv_buf.fill(static_cast<std::byte>(0));
    }

    return 0;
}
