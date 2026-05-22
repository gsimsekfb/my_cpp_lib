#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

//// Local static objects
// - Local static objects are initialized once on first call and destroyed 
//   when the program exits — thread-safe since C++11.
//
//// destruction order — reverse of construction
// local statics destroyed in reverse order of their initialization
// across TUs: order of destruction matches reverse of construction order ✓
//
//// Key notes:
// - initialized on first call — not at program start (lazy)
// - destroyed at program exit — reverse construction order
// - thread-safe initialization since C++11 — no manual mutex needed
// - combine with constinit (C++20) for compile-time init guarantee
// - static local vs static member: local = lazy; member = eager at startup
// - singleton via local static is the safest C++ singleton pattern


//// singleton pattern — most common use
class Logger {
public:
    static Logger& instance() {
        static Logger log;   // created once on first call ✓
        return log;          // thread-safe since C++11
    }
private:
    Logger() {}              // private constructor
};

TEST_CASE("loc-sta-1") {
    Logger logger = Logger::instance();
}


TEST_CASE("loc-sta-2") {

    struct Foo {};
    //// thread safety — C++11 guarantees
    static Foo obj; // if two threads call simultaneously:
                    // one initializes, other waits until ctor ends — no race ✓
                    // guaranteed by standard since C++11
}


//// basic — initialized once, persists across calls
int fn() {
    static int count = 0;   // initialized once ✓
    return ++count;
}

TEST_CASE("loc-sta-3") {
    REQUIRE(fn() == 1);
    REQUIRE(fn() == 2);
    REQUIRE(fn() == 3);
}


//// lazy initialization — only created if needed
string loadFile() { return "abc"; }

std::string& getConfig() {
    static std::string config = loadFile(); // loaded once, on first call ✓
    return config;
}


//// combine with constinit — C++20
void foo() {
    static constinit int x = 42;  // compile-time init + static lifetime ✓
        // constinit removes lazy-ness of static, moves the init to compile time
}

}