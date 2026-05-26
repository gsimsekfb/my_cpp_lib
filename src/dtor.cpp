#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// dtor
// - Throwing exceptions from destructors is extremely dangerous — if a 
//   destructor throws during stack unwinding (aka another exception was
//   thrown), std::terminate (=crash) is called immediately.
//
// Key notes:
// - throwing in constructor is fine — object not fully constructed, no dtor called


TEST_CASE("dtor-1") {

    //// the problem — throwing dtor during stack unwinding
    struct Foo {
        // ~Foo() { throw std::runtime_error("oops"); }  // ❌ dangerous
    };

    auto fn = []() {
        Foo f;
        throw std::runtime_error("first");  // stack unwinds, ~Foo() called
        // ~Foo() throws second exception → std::terminate() → crash 💥
    };


    //// rule — destructors must never throw,
    //// always catch and swallow exceptions inside destructors
    struct Foo_ {
        ~Foo_() noexcept {     // ✓ noexcept — compiler warning if throws
            try {
                // cleanup(); // may throw
            } catch (...) {
                // swallow — log but never rethrow ✓
            }
        }
    };


    //// noexcept — destructors are implicitly noexcept since C++11
    struct Foo__ {
        ~Foo__() {}                  // implicitly noexcept(true) ✓
        // ~Foo__() noexcept(false) {}  // opt out — dangerous, avoid
    };


    //// detect if unwinding — std::uncaught_exceptions (C++17)
    struct Guard {
        int exceptions = std::uncaught_exceptions();
            // active exceptions count at construction time - normally 0

        ~Guard() noexcept {
            if (std::uncaught_exceptions() > exceptions) {
                // we are stack unwinding — an exception was already thrown
                // don't throw, just cleanup
                // cleanup();
            } else {
                // normal exit — safe to throw if needed
                // commit();
            }
        }
    };


    // R
    //// RAII — correct pattern, no throwing dtor needed
    struct FileHandle {
        FILE* f = nullptr;

        FileHandle(const char* path) {
            if (fopen_s(&f, path, "r") != 0)
                throw std::runtime_error("open failed");  // ✓ throw in ctor ok
        }

        ~FileHandle() noexcept {
            // ✓ fclose doesn't throw — safe in dtor
            if (f && fclose(f) != 0) {
                // throw std::runtime_error("close failed");  // ❌ dangerous
                println("file close failed"); // OK, log instead of throw 
            }
        }
    };



}

}