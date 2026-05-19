#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"
#include <shared_mutex>

using namespace std;

namespace {

// std::shared_timed_mutex - Rust equivalent — RwLock<T>
// - allows multiple concurrent readers or one exclusive writer — the classic 
//   readers-writer lock.
//
// Key notes:
// - shared_lock  = read lock  — many threads simultaneously
// - unique_lock  = write lock — one thread, blocks everyone
// - C++14: shared_timed_mutex (with timeout support)
// - C++17: shared_mutex (no timeout — slightly faster)
// - use when reads are frequent and writes are rare
// - mutable keyword needed for mutex in const methods


TEST_CASE("shared-mut-1") {

    //// basic usage

    std::shared_timed_mutex mtx;
    std::string data = "hello";

    // read — multiple threads can hold simultaneously
    // void reader() 
    {
        std::shared_lock lock(mtx);   // shared (read) lock
        std::cout << data;            // multiple readers allowed ✓
    }

    // write — exclusive, blocks all readers and writers
    // void writer() 
    {
        std::unique_lock lock(mtx);   // exclusive (write) lock
        data = "world";               // only one writer at a time ✓
    }


    //// timed — try to acquire with timeout
    // function attempts to acquire a shared (read-only) lock on a mutex 
    // (`mtx`) within a 100-ms time limit; if successful, it prints `data`, 
    // and if the time limit expires before acquiring the lock, it prints 
    // "timeout".

    // void timedReader() 
    {
        std::shared_lock lock { mtx, std::chrono::milliseconds(100) };
        if (lock.owns_lock())
            std::cout << data;
        else
            std::cout << "timeout\n";
    }


    //// practical — cached value with read-heavy workload
    struct Cache {
        mutable std::shared_timed_mutex mtx;
        std::map<int, std::string> store;

        std::string get(int key) const {
            std::shared_lock lock(mtx);       // many readers ✓
            return store.at(key);
        }

        void set(int key, std::string val) {
            std::unique_lock lock(mtx);       // exclusive write ✓
            store[key] = std::move(val);
        }
    };


}

}