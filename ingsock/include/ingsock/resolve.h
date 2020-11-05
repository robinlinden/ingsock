#ifndef INGSOCK_RESOLVE_H
#define INGSOCK_RESOLVE_H

#include "ingsock/ip_addr.h"

#include <vector>

namespace ingsock {

std::vector<IpAddr> resolve(const char *name);

} // namespace ingsock

#endif
