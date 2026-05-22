#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// reinterpret_cast
// - reinterprets the raw bits of a pointer as a completely different type,
//   the most dangerous cast, no conversion performed.
// - legitimate uses: hardware registers, serialization via uint8_t*, opaque
//   handles (a void* or integer handle returned by a C API)
//
// Key notes:
// - no conversion — just tells compiler to treat bits as different type
// - prefer std::bit_cast (C++20) for safe type-punning
// - prefer memcpy for reading float bits safely in C++17 and earlier
// - if you reach for reinterpret_cast — question whether you need it


TEST_CASE("rei-cas-1") {

    //// pointer to integer and back
    int x = 42;
    uintptr_t addr = reinterpret_cast<uintptr_t>(&x);  // pointer → integer
    int* p = reinterpret_cast<int*>(addr);              // integer → pointer ✓
        // only safe if cast back to original type


    //// reinterpret bytes — read struct as raw bytes
    struct Packet { uint32_t id; float value; };
    Packet pkt {1, 3.14f};

    uint8_t* bytes = reinterpret_cast<uint8_t*>(&pkt);  // view as bytes ✓
        // useful for serialization, networking, binary protocols

}

}