#include "ingsock.h"

#include <array>
#include <iostream>

using namespace ingsock;

int main(int, char **) {
    Socket s{Domain::ipv4, Type::tcp};

    if (!s.bind(SocketAddrV4{IpAddrV4::any(), 22222})) {
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
    const auto msg{std::to_array("hello client")};
    if (client.send(msg) != static_cast<int>(msg.size())) {
        const int err = last_error();
        std::cerr << "Failed to send message: " << err << std::endl;
    }

    return 0;
}
