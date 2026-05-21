#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <algorithm>

#include "utils.h"

using namespace std;


TEST_CASE("erase-1") {
    
    //// (1) erase - remove by value
    vector vec = {1, 2, 3, 3};
    // cpp20
    auto res = std::erase(vec, 3); // res: # of elems erased
    REQUIRE(res == 2);
    REQUIRE(vec == vector {1,2});
    // cpp11 - erase-remove idiom
    vec.erase(std::remove(vec.begin(), vec.end(), 2), vec.end());
    REQUIRE(vec == vector {1});


    //// (2) eras_if - remove by predicate

    /// a
    vector vec_ = {1, 2, 3, 3, 4};
    // cpp20
    auto res_ = std::erase_if(vec_, [](auto e) { return e < 3; }); 
        // res_: # of elems erased
    REQUIRE(res_ == 2);
    REQUIRE(vec_ == vector {3,3,4});


    /// b
    std::map<int, string> map { {-1, "a"}, { 2, "b" }, {-3, "c"}, {4, "d"} };
    REQUIRE(map.size() == 4);

    //// erase by keys
    // cpp20
    std::erase_if(map, [](const auto& pair) { return pair.first < 0; } );
    REQUIRE(map.size() == 2);
    REQUIRE(map == std::map<int, string> { {4, "d"}, {2, "b" }});    

    // cpp11
    // there's no `std::remove` equivalent for `map` since map elements aren't 
    // contiguous.

    // pre-cpp11 (auto - cp11)
    for(auto it = map.begin(); it != map.end(); ) {
        if(it->first > 0) 
            it = map.erase(it); // erase already iterates
        else
            ++it;
    }

    REQUIRE(map.size() == 0);
}
