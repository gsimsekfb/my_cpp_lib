#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-parameter"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {


// static fn
// - 
//
// Key notes:
// - static member fn: no this, no instance needed, called via ClassName::fn()
// - static free fn: internal linkage — not visible outside TU
// - cannot be virtual — no this pointer, no vtable dispatch
// - common uses: singleton, factory, utility/helper, validation


//// static member function — belongs to class, not object
struct Math {
    int val = 0; 
    static int square(int x) { 
        // ++val; // ❌ no this — can't access instance members
        return x * x; 
    }
    // static int PI = 3;   // ❌ must be constexpr or inline
    static constexpr double PI  = 3.14159;   // compile-time and const
    static inline    double PI_ = 3.14159;   // runtime and mut
};

struct Logger {
    static void log() { count++; } 
        // Static member function can access private static member
private:
    static inline int count = 0;   // Private static data member
};


//// static free function — internal linkage (C-style)
// file.cpp
static void helper() {} // only visible in this TU ✓
                        // same as anonymous namespace

// anonymous namespace — prefer in modern C++
namespace {
    void helper() {}      // internal linkage ✓ — C++11 preferred way
}


//// static local function variable
void fn() {
    static int count = 0;   // persists across calls — see local statics ✓
}


//// common uses
struct Config {
    static Config& instance() {           // singleton ✓
        static Config cfg;
        return cfg;
    }

    static Config fromFile(std::string path) {  // factory ✓
        Config c;
        // c.load(path);
        return c;
    }

    static bool isValid(std::string key) { // utility ✓
        return !key.empty();
    }
};



}