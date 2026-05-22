#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// const_cast
// - const_cast is the only cast that can add/remove const (or volatile)
//   from a type.
// - main legitimate use: interop with legacy C APIs lacking const correctness
// - if you need const_cast a lot — fix the API instead
//
// Key notes:
// - only cast that adds/removes const and volatile — nothing else
// - removing const is safe ONLY if original object was not declared const
// - modifying a truly const object after const_cast = UB
// - prefer mutable over const_cast for class members


//// remove const — call legacy C API that isn't const-correct
void c_api(char* s) {  // old C API — doesn't modify s but not const
    printf("%s", s);
}

TEST_CASE("con-cas-1") {

    const char* msg = "hello";
    c_api(const_cast<char*>(msg)); // ✓ safe — c_api doesn't modify it


    //// remove const — only safe if original object was not const
    const int* ptr = new int(42); // pointer to const int, !! but underlying 
                                  // object is still not const !! 
    int* mp = const_cast<int*>(ptr);
    *mp = 99;                      // ✓ safe — original object was non-const
    REQUIRE(*ptr == 99);
    delete ptr;

    const int x = 42; // !! underlying object is const !!
    int* mut_ptr = const_cast<int*>(&x);
    *mut_ptr = 99;                 // ❌ UB — original object IS const
    REQUIRE(x == 42);


    //// add const — rarely needed, implicit conversion does this
    int xx = 42;
    [[maybe_unused]]
    const int* p = const_cast<const int*>(&xx);
        // ✓ but just use: const int* p = &x;


    //// mutable member — alternative to const_cast
    struct Cache {
        // cpp98
        mutable int hits = 0; // prefer mutable over const_cast
        int get() const {
            hits++;           // ✓ mutable — no const_cast needed
            return 42;
        }
    };



}

}