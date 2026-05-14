#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// designated init.
// - Designated initializers let you initialize struct members by name instead
//   of position.
//
// Key notes:
// - Best pattern: use as named function arguments via a params struct
// - Aggregate types only (types w/ no constructors, no private members)
// - Must follow declaration order — skipping is fine, reordering is not
// - Skipped fields are zero/default initialized


TEST_CASE("des-ini-1") {
    // before cpp20 — positional, fragile
    struct Config { int width, height, depth; bool vsync; };

    Config c = {1920, 1080, 32, true};
        // which is width? which is depth? easy to swap ❌

    // cpp20 — named, self-documenting
    Config c_ = {
        .width  = 1920,
        .height = 1080,
        .depth  = 32,
        .vsync  = true
    };

    REQUIRE(c_.width == 1920);
}



