#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

TEST_CASE("std-format-1") {
    string name = "alex";
    int id = 42;
    string str = std::format("hello {}, id {}", name, id);
    REQUIRE(str == "hello alex, id 42");

    // floats
    string str2 = std::format("{:.2f}", 3.14159);     // "3.14"
    REQUIRE(str2 == "3.14");

    // integers
    (void) std::format("{:d}", 255); // "255"       (decimal)
    (void) std::format("{:b}", 255); // "11111111"  (binary)
    (void) std::format("{:x}", 255); // "ff"        (hex)
}
