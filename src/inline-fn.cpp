#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// inline fn
// - inline suggests the compiler replace the call with the fn body — but main
//   modern use is allowing definition in headers without *ODR violations.
//   *ODR: One Definition Rule
//
// Key notes:
// - too much inlining: code bloat — larger binary, worse cache performance
// - too little inlining: call overhead — worse for tiny frequently called fns


//// basic — hint to compiler to inline
// - inline as optimization hint: compiler may ignore — it knows better
inline int square(int x) { return x * x; }
    // original intent — avoid function call overhead present without inline:
    // call square(5) → push args → jump → execute → return → jump back
    //
    // with inline (if compiler agrees):
    // int result = 5 * 5;  — substituted directly ✓


//// compiler ignores the hint
inline void hugeFn() {
    // 500 lines of code
}
    // compiler will NOT inline this — too large
    // inline is just a suggestion — compiler decides ✓


//// force inline — compiler-specific
// - __forceinline / always_inline: force it — use only in hot paths
/* 
__forceinline int sq(int x) { return x * x; }  // MSVC
__attribute__((always_inline)) int sq_(int x) {} // GCC/Clang

*/


//// modern main use — ODR (one definition rule) - not a hint, always works
// without inline — linker error if included in multiple TUs
// header.h
int square_(int x) { return x * x; }   // ❌ multiple definition error

// with inline — safe in headers
inline int square__(int x) { return x * x; }  // ✓ one logical definition


//// constexpr implies inline
constexpr int square___(int x) { return x * x; }  // implicitly inline ✓


//// inline class methods — implicitly inline
struct Foo {
    int square(int x) { return x * x; }  // defined in class body = inline ✓
};


//// inline variable — C++17
inline int MAX_USERS = 100;   // safe in headers, shared across TUs ✓
    // use it for global variable like MAX_USERS is to create a single,  
    // header-only global constant or configuration setting that is shared 
    // across multiple source files without causing duplicate symbol errors 
    // at link time. 
    // !! mutable global variables are strongly discouraged in modern C++ due 
    // to thread-safety risks, hidden dependencies, and testing difficulties, 
    // though global constants (inline constexpr) are widely accepted.


//// lambda — always inline candidate
auto sq_lam = [](int x) { return x * x; };  // compiler almost always inlines ✓



}