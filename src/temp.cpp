#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <algorithm>

#include "utils.h"

TEST_CASE("map-2") {
    std::map<int, std::string> map { {-1, "a"}, { 2, "b" }, {-3, "c"}, {4, "d"} };
    REQUIRE(map.size() == 4);
}