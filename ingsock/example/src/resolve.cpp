#include "ingsock.h"

#include <iostream>
#include <variant>

using namespace ing;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " example.com" << std::endl;
        return 0;
    }

    const auto ips = resolve(argv[1]);
    if (ips.empty()) {
        std::cout << "Unable to resolve host" << std::endl;
        return 1;
    }

    std::cout << "Resolved host to the following ips:\n";
    for (const auto &ip : ips) {
        std::visit([](auto ip) { std::cout << ip << '\n'; }, ip);
    }

    return 0;
}
