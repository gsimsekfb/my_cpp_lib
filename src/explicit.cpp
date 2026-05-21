#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-parameter"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// explicit
// - 
//
// Key notes:
// - explicit on constructor: blocks implicit conversions and copy-init
// - explicit on operator: blocks implicit conversion in assignments
// - C++20: explicit(bool) — conditionally explicit based on type trait
// - rule of thumb: mark single-arg constructors explicit unless conversion 
//   is intended
// - std::string is NOT explicit from const char* — intentional convenience

//// use case 1 — prevent implicit single-arg construction
struct Radius { double r; explicit Radius(double r) : r(r) {} };
void draw(Radius r) { };

TEST_CASE("explicit-1") {

    // draw(5.0);        // ❌ implicit conversion blocked
    draw(Radius{5.0});   // ✓ explicit conversion


    //// use case 2 — prevent implicit bool conversion
    struct Handle {
        explicit operator bool() const { return valid; }
        bool valid = true;
    };
    Handle h;
    if (h) {}         // ✓ explicit bool context
    // bool b = h;    // ❌ implicit conversion blocked

}

}