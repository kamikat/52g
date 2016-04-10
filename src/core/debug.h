#ifndef DEBUG_H
#define DEBUG_H

#ifndef NDEBUG
#include <iostream>
#include <iomanip>
#define DEBUG(expr) std::cerr << "DEBUG " << expr << std::endl
#define HEX(x) std::setw(2) << std::setfill('0') << std::hex << (uint64_t)(x) << std::setw(0) << std::dec
#else
#define DEBUG(expr)
#endif

#endif
