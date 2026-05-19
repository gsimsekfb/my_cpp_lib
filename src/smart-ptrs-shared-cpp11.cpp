#include <mutex>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

//// shared_ptr<T> — shared ownership, atomic ref counted
// !! shared_ptr ref count  — atomic ✓ thread-safe
// !! T                     — NOT atomic, needs separate synchronization
//
// shared_ptr<T> + external mutex  ≈  Arc<Mutex<T>>   (shared + mutable)
// shared_ptr<const T>             ≈  Arc<T>          (shared + immutable)
//
// - multiple owners, freed when last owner dies (ref count = 0)
// - atomic ref count — thread-safe but ~2x overhead vs unique_ptr
//
// Key notes:
// - never pass a share_ptr internal raw ptr (.get()) to another shared_ptr,
//   will be double free. Instead use: shared_ptr<int> q = p;
// - cycles: A→B→A keeps both alive forever — use weak_ptr to break
// - Rust Arc<T>: same model, but no cycles possible via borrow checker
// - Rust Rc<T>: non-atomic version — C++ has no equivalent 
//   (shared_ptr always atomic)

class MyClass {
    int x;
    public: MyClass(int x) : x(x) {  }
    int getX() { return this->x; };
};

class Base {};
class Derived : public Base {};

TEST_CASE("shared-ptr-1") {

    //// create
    auto ptr = std::make_shared<int>(42);          // ✓ prefer — one allocation
    auto ptr_ = std::shared_ptr<int>(new int(42));  // two allocations — avoid
        // allocates the int separately first, then shared_ptr allocates the
        // control block (internal bookkeeping struct storing the reference 
        // count, weak reference count, and custom deleter) separately.

    
    //// copy / share ownership
    auto a = std::make_shared<int>(42);
    auto b = a;                   // ref count = 2 — both own it
    auto c = a;                   // ref count = 3
        // freed when a, b, c all go out of scope


    //// access
    *a;            // dereference
    a.get();       // raw pointer — don't store
    // a->method();   // arrow access
    a.use_count(); // current ref count


    //// reset / release
    a.reset();                    // decrement count, a = nullptr
    a.reset(new int(99));         // decrement old, own new


    //// move — transfer without incrementing count
    auto d = std::move(a);        // a = null, count stays same ✓


    //// polymorphism
    std::shared_ptr<Base> p = std::make_shared<Derived>();

}


//// Multithreading

// mutex and data can be wrapped in an object but they are still not as
// connected as in Rust: let counter = Arc::new(Mutex::new(0));
struct SharedCounter {
    std::mutex mtx;
    int value;
};

TEST_CASE("shared-ptr-2") {
    auto counter = std::make_shared<SharedCounter>();

    // Take the shared_ptr as a parameter instead of capturing it
    auto increment = [](std::shared_ptr<SharedCounter> counter) {
        for (int i = 0; i < 10; ++i) {
            std::lock_guard lock(counter->mtx);
            counter->value++;
        }
    };

    // counter is safely copied sequentially here
    std::thread t1(increment, counter);
    std::thread t2(increment, counter);
    
    t1.join();
    t2.join();

    std::lock_guard lock(counter->mtx);
    REQUIRE(counter->value == 20);
}
//// Rust
/* 
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let counter = Arc::new(Mutex::new(0));

    let handles: Vec<_> = (0..2).map(|_| {
        let c = Arc::clone(&counter);
        thread::spawn(move || {
            for _ in 0..1000 {
                *c.lock().unwrap() += 1;
            }
        })
    }).collect();

    for h in handles { h.join().unwrap(); }

    println!("{}", *counter.lock().unwrap());  // 2000 ✓
}
*/

}