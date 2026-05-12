#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

TEST_CASE("using-enum-1") {

    enum class Color { Red, Green, Blue };

    using enum Color; // **

    Color color = Green;
    switch (color) {
        case Red:   println("red"); break;
        case Green: println("green"); break;
        case Blue:  println("blue"); break;
    }
}
