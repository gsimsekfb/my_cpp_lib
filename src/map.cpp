#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <algorithm>

#include "utils.h"

// cpp20
void erase_negatives_2020(std::map<int, std::string>& map) {
    std::erase_if(map, [](const auto& pair) { return pair.first < 0; } );
}

// cpp11
void erase_negatives_2011(std::map<int, std::string>& map) {
    for(auto it = map.begin(); it != map.end(); ) {
        if(it->first < 0) 
            it = map.erase(it);
        else
            ++it;
    }
}

TEST_CASE("map-1") {
    std::map<int, std::string> map { {-1, "a"}, { 2, "b" }, {-3, "c"}, {4, "d"} };
    REQUIRE(map.size() == 4);

    erase_negatives_2020(map);
    REQUIRE(map.size() == 2);
    std::map<int, std::string> map2 { {4, "d"}, {2, "b" }};
    REQUIRE(map == map2);
}