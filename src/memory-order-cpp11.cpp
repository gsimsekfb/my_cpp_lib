#include <atomic>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

//// memory order
// 6 memory orders — from strictest to most relaxed
// std::memory_order_seq_cst   — default, strongest, slowest
// std::memory_order_acquire   — pairs with release (load side)
// std::memory_order_release   — pairs with acquire (store side)
// std::memory_order_acq_rel   — both acquire and release (read-modify-write)
// std::memory_order_consume   — weak acquire (rarely used, avoid)
// std::memory_order_relaxed   — no ordering, fastest
//
//// key notes
// - default (seq_cst) is always correct — relax only for perf
// - acquire/release: most common optimization — producer/consumer pattern
// - relaxed: only safe when operations are truly independent
// - consume: avoid — compilers treat it as acquire anyway
// - wrong memory order = data race = UB — subtle, hard to debug
// - on x86: seq_cst is cheap (strong memory model); on ARM: expensive


TEST_CASE("mem-ord-1") {   

    //// problem - using relaxed order

    std::atomic<bool> ready = false;
    std::atomic<int> data = 0;

    // Thread 1
    data.store(42, std::memory_order_relaxed);
    ready.store(true, std::memory_order_relaxed);

    // Thread 2
    if (ready.load(std::memory_order_relaxed))
        // data might still be 0 here! CPU can reorder, 
        // Thread 2 may see ready=true but data=0
        std::cout << data.load(std::memory_order_relaxed);

    //// solved

    std::atomic<bool> ready_ = false;
    std::atomic<int> data_ = 0;

    // Thread 1
    data_.store(42, std::memory_order_relaxed);    // data doesn't need sync
    ready_.store(true, std::memory_order_release); // "publish" — everything 
                                                   // above is visible

    // Thread 2
    if (ready_.load(std::memory_order_acquire))   // "subscribe" — sees 
                                                  // everything before release
        cout << data.load(memory_order_relaxed);  // guaranteed to be 42
}


