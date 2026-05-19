#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

//// weak_ptr — non-owning observer  |  Rust: Weak<T>
// - observes a shared_ptr without affecting ref count
// - must lock() to access — safely handles object being destroyed
//
// Key notes:
// - weak_ptr never keeps object alive — purely observing
// - always check lock() result before use — never assume it's valid
// - Rust Weak<T>: same concept, upgrade() = lock(), also returns Option
// - main use cases: breaking cycles, caches, observer/event systems


TEST_CASE("weak-1") {

    //// create
    auto sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp;         // ref count stays 1 ✓

    //// access — must lock first
    if (auto locked = wp.lock()) {      // returns shared_ptr — empty if expired
        std::cout << *locked;           // ✓ object still alive
    } else {
        std::cout << "expired";         // sp was destroyed
    }

    //// check without locking
    wp.expired();                       // true if object gone
    wp.use_count();                     // current ref count (0 if expired)

    //// reset
    wp.reset();                         // release observation


    //// main use 1 — break cycles
    struct Node {
        shared_ptr<Node> next;
        // shared_ptr<Node> prev; // ❌ cycle if two nodes point to each other
        weak_ptr<Node>   prev;    // ✓ breaks cycle — no ref count bump
    };

}

}