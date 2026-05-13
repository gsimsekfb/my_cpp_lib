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
    // before
    vec.erase(std::remove(vec.begin(), vec.end(), 2), vec.end());
    REQUIRE(vec == vector {1});


    //// (2) eras_if - remove by predicate
    vector vec_ = {1, 2, 3, 3, 4};
    // cpp20
    auto res_ = std::erase_if(vec_, [](auto e) { return e < 3; }); 
        // res_: # of elems erased
    REQUIRE(res_ == 2);
    REQUIRE(vec_ == vector {3,3,4});
}
