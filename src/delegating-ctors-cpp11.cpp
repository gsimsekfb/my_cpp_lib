#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// delegating ctors
// - Delegating constructors let one constructor call another constructor of
//   the same class — avoiding code duplication.
//
// Key notes:
// - cannot mix delegation with member init in same constructor
//   Bar(int x) : Bar(0), member(x) {}  ❌ — either delegate or init members
// - primary constructor does the actual work — others delegate to it


//// with delegating — one place to init (C++11)
struct Config {
    std::string host;
    int port;
    bool ssl;

    Config(std::string h, int p, bool s)  // primary — does actual init
        : host(h), port(p), ssl(s) {}

    Config()                              // delegates to primary ✓
        : Config("localhost", 8080, false) {}

    Config(std::string h)                 // delegates to primary ✓
        : Config(h, 8080, false) {}

    Config(std::string h, int p)          // delegates to primary ✓
        : Config(h, p, false) {}
};


}