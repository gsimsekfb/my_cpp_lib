#include <stdexcept>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-parameter"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// 
// - 
//
// Key notes:


TEST_CASE("exc-1") {

    //// basic — throw and catch
    try {
        throw std::runtime_error("something went wrong");
    } catch (const std::runtime_error& e) {
        std::cout << e.what();   // "something went wrong"
    } catch (const std::exception& e) {
        std::cout << e.what();   // catch any std exception
    } catch (...) {
        // catch everything — last resort
    }

    //// standard exception hierarchy
    // std::exception
    // ├── std::runtime_error   — errors at runtime
    // │   ├── std::overflow_error
    // │   ├── std::underflow_error
    // │   └── std::range_error
    // ├── std::logic_error     — errors in program logic
    // │   ├── std::invalid_argument
    // │   ├── std::out_of_range
    // │   └── std::length_error
    // ├── std::bad_alloc       — new failed
    // ├── std::bad_cast        — dynamic_cast failed
    // └── std::bad_optional_access


    //// custom exception
    struct AppError : std::runtime_error {
        int code;
        AppError(int c, std::string msg) : std::runtime_error(msg), code(c) {}
    };

    try {
        throw AppError(404, "not found");
    } catch (const AppError& e) {
        std::cout << e.code << ": " << e.what();
    }


    //// rethrow
    try {
        // riskyOp();
    } catch (const std::exception& e) {
        // log(e.what());
        throw;              // ✓ rethrow same exception — not throw e (slicing)
    }


    //// exception in constructor — ok, destructor not called
    struct Foo {
        Foo() {
            throw std::runtime_error("init failed");  // ✓ safe to throw
        }
        ~Foo() {}   // never called if ctor throws ✓
    };


    //// key notes
    // - catch by const reference — avoid slicing, avoid copy
    // - catch most derived first — base catches everything below it
    // - throw; to rethrow — not throw e (that slices)
    // - noexcept enables compiler optimizations — use on move constructors
    // - std::terminate on: exception in noexcept fn, uncaught exception, dtor throw
    // - RAII is the correct way to handle cleanup — not try/finally
    // - exceptions have overhead only when thrown — zero cost on happy path (usually)

}

    //// noexcept — promise not to throw
    void fn()   noexcept { /* if exception escapes → std::terminate */ }
    void fn_()  noexcept(true)  {} // same as noexcept
    void f1() {}                  // no noexcept
    void f1_() noexcept(false) {} // may throw — same as no noexcept

    // conditional noexcept
    template<typename T>
    void swap(T& a, T& b) noexcept(std::is_nothrow_move_constructible_v<T>) {}


    //// noexcept check at compile time
    static_assert(noexcept(fn()));   // ✓ verify fn is noexcept


    //// stack unwinding — RAII handles cleanup
    void foo() {
        // FileHandle f("file.txt"); // RAII — dtor called even if throw ✓
        throw std::runtime_error("error");
    }   // ~FileHandle() called here — file closed ✓


    //// function try block — catch in constructor
    int throwing_fn() { throw std::runtime_error("err"); }
    struct Foo {
        int xx;
        Foo() try : xx(throwing_fn()) {
            std::cout << "Foo successfully created.\n"; // Never reached
        } catch (const std::exception& e) {
            std::cout << "Log: Caught error in ctor: " << e.what() << "\n";
            // The exception is automatically rethrown here by the compiler!
        }
    };

    // b. try block "inside" ctor
    struct MyServer {
        // DatabaseConnection db; 
            // If this throws, the inside try-catch is bypassed entirely!

        MyServer() {
            try {
                // This only catches exceptions thrown here inside the body
                throw std::runtime_error("Body error"); 
            } 
            catch (const std::runtime_error& e) {
                std::cout << "Logged and swallowed: " << e.what() << "\n";
                // No auto-rethrow! MyServer is successfully created.
            }
        }
    };

}