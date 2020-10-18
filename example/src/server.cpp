#include "ingsock.h"

#include <cstddef>
#include <iostream>

using namespace ingsock;

int main(int, char **) {
    Socket s{Domain::ipv6, Type::stream, Protocol::tcp};

    std::array<std::byte, 16> ip{};
    if (!s.bind(SocketAddrV6{IpAddrV6{ip}, 22222})) {
        const int err = last_error();
        std::cerr << "Failed to bind to port: " << err << std::endl;
        return 1;
    }

    if (!s.listen(10)) {
        const int err = last_error();
        std::cerr << "Failed to listen: " << err << std::endl;
        return 1;
    }

    Socket client{s.accept()};
    const std::string msg{"hello client"};
    if (client.send(reinterpret_cast<const std::byte *>(msg.data()), msg.size()) != msg.size()) {
        const int err = last_error();
        std::cerr << "Failed to send message: " << err << std::endl;
    }

    return 0;
}
