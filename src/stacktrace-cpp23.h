#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <print>
#include <stacktrace>

#include "utils.h"

using namespace std;

namespace {

// Concepts
// - 
//
// Key notes:
// - C++23 — #include <stacktrace>
// - std::stacktrace::current() — captures at call site
// - current(skip, depth) — control how many frames to capture
// - capture at throw site not catch site — store in exception object ✓
// - requires debug info for meaningful output (-g on GCC/Clang)

TEST_CASE("stack-1") {

    //// capture current stack
    auto trace = std::stacktrace::current();
    std::println("-- {}", std::to_string(trace));  // print full trace ✓
    std::println("--\n");


    //// in exception handler
    try {
        // riskyOp();
        throw std::bad_exception();
    } catch (const std::exception& e) {
        auto trace = std::stacktrace::current();
        std::println("-- error: {}", e.what());
        std::println("-- trace:\n{}", std::to_string(trace));
    }
    std::println("--\n");


    //// custom exception with stacktrace
    struct AppError : std::runtime_error {
        std::stacktrace trace;

        AppError(std::string msg)
            : std::runtime_error(msg)
            , trace(std::stacktrace::current()) {}  // capture at throw site ✓
    };

    try {
        throw AppError("something failed");
    } catch (const AppError& e) {
        std::println("-- error: {}", e.what());
        std::println("-- trace:\n{}", std::to_string(e.trace));
    }
    std::println("--\n");


    //// iterate entries manually
    auto trace_ = std::stacktrace::current();
    for (const auto& entry : trace_) {
        std::println("-- file: {}, line: {}, in fn: {}",
            entry.source_file(),   // filename
            entry.source_line(),   // line number
            entry.description());  // function name ✓
    }
    std::println("--\n");


}

}