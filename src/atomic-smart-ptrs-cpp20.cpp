#include <memory>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// atomic smart ptrs
// - std::atomic<std::shared_ptr<T>> and 
//   std::atomic<std::weak_ptr<T>> are added as first-class specializations — 
//   replacing the deprecated free functions std::atomic_load/store.
//
// Key notes:
// - Old std::atomic_load/store free functions are deprecated — don't use them
// - Atomicity covers the pointer itself, not the pointed-to object
// - Best use case: shared immutable config/state swapped wholesale by one 
//   writer
// - compare_exchange enables optimistic lock-free updates
// - atomic<weak_ptr> = observe shared resource without extending its lifetime
// - is_lock_free() may return false — may use internal mutex on some platforms


TEST_CASE("ato-shr-1") {

    //// now
    atomic<shared_ptr<int>> atom_ptr = std::make_shared<int>(42);
        REQUIRE(*atom_ptr.load() == 42);
    // standard atomic operations
    auto shared_ptr = atom_ptr.load();         // atomic read ✓
    atom_ptr.store(std::make_shared<int>(99)); // atomic write ✓
        REQUIRE(*atom_ptr.load() == 99);
    auto old = atom_ptr.exchange(std::make_shared<int>(0)); // swap ✓

    //// before
    std::shared_ptr<int> ptr = std::make_shared<int>(42);
    println(ptr); println(*ptr);
        // 0000022B2ECD9040
        // 42

    // old way — deprecated in C++20
        // warning STL4029: std::atomic_*() overloads for shared_ptr are 
        // deprecated in C++20
    std::shared_ptr<int> ptr_old = std::atomic_load(&ptr);
    std::atomic_store(&ptr, std::make_shared<int>(99));
        // both ptr(address) itself and its val changed
    println(ptr); println(*ptr);
        // 0000022B2ECD9080
        // 99

    println(ptr_old); println(*ptr_old);
        // 0000022B2ECD9040
        // 42

    // REQUIRE(maxConnections == 128);
}

