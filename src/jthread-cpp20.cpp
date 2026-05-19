#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"
#include <thread>

using namespace std;

namespace {

// std::jthread
// - is std::thread with automatic joining on destruction and
//   with built-in stop token for cooperative cancellation (A flag the thread 
//   can check at any point to know if it's been asked to stop — the thread 
//   decides when/how to exit cleanly rather than being killed from outside).
//
// Key notes:
// - jthread joins automatically — no risk of std::terminate on destruction
// - destructor calls request_stop() then join() automatically
// - prefer jthread over thread in all new code — strictly better
// - std::thread has no cancellation mechanism at all; you have to implement 
//   it yourself with a shared `atomic<bool>` flag.


//// 1. problem w/ std::thread

// the real problem with std::thread is that its dtor does not auto-joins.
// It was a deliberate design decision (to avoid silent performance surprises 
// from unexpected blocking in destructors), but it means you must always 
// explicitly manage join/detach, which `std::jthread` fixes in C++20.

void processLargeFile() {}

TEST_CASE("jthread-1") {

    std::thread t1 { []{ processLargeFile(); } };

    try {
        // validateInput();  // throws on bad input
    } catch (...) {
        // return 1;  // ❌ exception caught, early return — but 
                      // t never joined — std::terminate
        // `std::terminate` kills the entire process immediately, so
        // `processLargeFile()` is abruptly killed mid-execution — 
        // potential data corruption, incomplete writes, unclosed file
        // handles, etc.                      
    }

    t1.join();
}


//// 2.  w/ jthread

void processLargeFile_() {}

TEST_CASE("jthread-2") {

    std::jthread t1([]{ processLargeFile_(); });

    try {
        // validateInput();
    } catch (...) {
        return;  // ✓ safe — jthread auto-joins on destruction
    }
}


//// 3.  w/o jthread (pre-cpp20) solution

struct JoinGuard {
    std::thread& t; // ref ??
    ~JoinGuard() { if (t.joinable()) t.join(); }  // **
};

TEST_CASE("jthread-3") {

    std::thread t1 { []{ processLargeFile(); } };
    JoinGuard guard { t1 };  // joins automatically on any exit path
    
    // if (!loadConfig()) return 1;  // ✓ safe — guard joins t
}


}
