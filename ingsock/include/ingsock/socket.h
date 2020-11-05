#ifndef INGSOCK_SOCKET_H
#define INGSOCK_SOCKET_H

#include "ingsock/socket_addr.h"

#include <cstddef>

namespace ingsock {

enum class Domain {
    ipv4,
    ipv6,
};

enum class Type {
    stream,
    dgram,
};

enum class Protocol {
    tcp,
    udp,
};

enum class Shutdown {
    receive,
    send,
    both,
};

class Socket {
public:
    Socket(Domain d, Type t, Protocol p);
    explicit Socket(int socket);

    Socket(const Socket &) = delete;
    Socket &operator=(const Socket &) = delete;

    Socket(Socket &&) noexcept;
    Socket &operator=(Socket &&) noexcept;

    ~Socket();

    bool connect(SocketAddr addr);
    bool bind(SocketAddr addr);
    bool listen(int backlog);
    Socket accept();

    int shutdown(Shutdown what);
    int close();

    int recv(std::byte *buf, int len);
    int send(const std::byte *buf, int len);

    template<class T>
    int recv(T *buf) {
        return recv(reinterpret_cast<std::byte *>(buf->data()), buf->size());
    }

    template<class T>
    int send(const T &buf) {
        return send(reinterpret_cast<const std::byte *>(buf.data()), buf.size());
    }

private:
    // Technically sockets are 64-bit on Windows x64, but
    // things like OpenSSL receive it as an int in their
    // API, so this is unlikely to ever break.
    int socket_;
};

} // namespace ingsock

#endif
