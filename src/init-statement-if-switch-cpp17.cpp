// #pragma once
#include <map>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// Concepts
// - 
//
// Key notes:


TEST_CASE("ini-sta-if-1") {

    //// 1. if

    // now
    auto map = std::map<int, char> { {1, 'a'} };
    if (auto it = map.find(1); it != map.end())
        REQUIRE(it->second =='a'); // it scoped to if block only ✓

    // before, it leaks into outer scope
    auto it = map.find(1);     // it visible here too — unintended
    if (it != map.end())
        std::cout << it->second;


    //// 2. switch
    auto getStatus = []()->int { return 42; }; 
    switch (auto status = getStatus(); status) {
        case 0:  REQUIRE(status == 0);  break;
        case 42: REQUIRE(status == 42); break;
    }
    // status not visible here ✓

}
