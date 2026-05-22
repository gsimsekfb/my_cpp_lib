#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// extern
// - extern declares a variable or function that is defined elsewhere — 
//   in another translation unit or a C library.
//
// Key notes:
// - extern variable: declaration only — definition must exist exactly once
// - extern "C": prevents C++ name mangling — required for C interop
// - extern template (C++11): avoid duplicate template instantiations
// - missing definition → linker error; duplicate definition → linker error
// - prefer inline variables (C++17) over extern for shared constants


//// 1

/// extern variable — declare without defining
// file_a.cpp
int counter = 0;     // definition — memory allocated here

// file_b.cpp
extern int counter;  // declaration — no memory, just tells compiler it exists
// counter++;        // ✓ uses file_a.cpp's counter
    // This is Not init-order fiasco.
    // init-order fiasco:
    // - one global's initializer depends on another global from a different 
    //   translation unit.

/// C++17 inline — define in header, mutable, shared across all TUs
// config.h
inline std::string host = "localhost";  // ✓ no .cpp needed
inline int port = 8080;                 // ✓ same instance across all TUs

/// cpp20 with constinit — guarantee compile-time init
inline constinit int port_ = 8080;      // mutable + compile-time init ✓


//// 2. extern "C" — C linkage, no name mangling
// expose C++ function to C code
extern "C" void myFunc() { } // callable from C ✓

// call C library function from C++
extern "C" {
    // #include <some_c_library.h>   // all declarations use C linkage ✓
}

// common pattern — header usable from both C and C++
#ifdef __cplusplus
extern "C" {
#endif
    void c_api_func(int x);
#ifdef __cplusplus
}
#endif


//// extern vs static — opposite linkage
int a = 0;          // external linkage — visible to other TUs
extern int a;       // declare it in another TU
static int b = 0;   // internal linkage — only visible in this TU


//// extern template — C++11, prevent implicit instantiation

// header.h
// extern template class std::vector<MyClass>;  // don't instantiate here

// file.cpp
// template class std::vector<MyClass>;         // instantiate exactly once ✓
    // avoids duplicate instantiation across TUs — faster compile times


TEST_CASE("extern-1") {


}

}