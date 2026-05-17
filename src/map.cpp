#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <map>

#include "utils.h"

using namespace std;

// cpp20
void erase_negatives_2020(std::map<int, string>& map) {
    std::erase_if(map, [](const auto& pair) { return pair.first < 0; } );
}

// cpp11
void erase_negatives_2011(std::map<int, string>& map) {
    for(auto it = map.begin(); it != map.end(); ) {
        if(it->first < 0) 
            it = map.erase(it);
        else
            ++it;
    }
}

TEST_CASE("map-1") {

    //// define map
    std::map<int, string> map { {-1, "a"}, { 2, "b" }, {-3, "c"}, {4, "d"} };
    REQUIRE(map.size() == 4);

    //// erase negative key elems
    erase_negatives_2020(map);
    REQUIRE(map.size() == 2);
    REQUIRE(map == std::map<int, string>{ {4, "d"}, {2, "b" }});

    //// if init statement cpp17
    if (auto [it, ok] = map.insert({1, "z"}); ok)
        std::cout << "inserted\n";   // structured binding in init ✓
}