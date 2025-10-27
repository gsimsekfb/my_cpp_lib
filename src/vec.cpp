#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <algorithm>

#include "utils.h"

// cpp20
void erase_negatives_2020(std::vector<int>& vec) {
    std::erase_if(vec, [](int e) { return e < 0; } );
}

// cpp11
void erase_negatives_2011(std::vector<int>& vec) {
    vec.erase(
        std::remove_if(vec.begin(), vec.end(), [](int e ) { return e < 0; }),
        vec.end()
    );
}

// cpp-pre-11 (needed?, read for iterator invalidation issue)
void erase_negatives_pre_cpp11(std::vector<int>& vec) {
    for (auto it = vec.begin(); it != vec.end();) {
        // dbg(vec.size()); // dbg(*it);
        if (*it < 0) {
            it = vec.erase(it); // !! iterator invalidation risk, vec may resize
        } else {
            ++it;
        }
    }
}

TEST_CASE("vec-1") {
    std::vector<int> v1 { -1, 2, -3, 4, -5};
    REQUIRE(v1.size() == 5);

    erase_negatives_pre_cpp11(v1);
    REQUIRE(v1.size() == 2);
    std::vector<int> v2 { 2, 4};
    REQUIRE(v1 == v2);
}

TEST_CASE("vec-2") {
    std::vector<int> v1 { -1, 2, -3, 4, -5};
    REQUIRE(v1.size() == 5);

    erase_negatives_2011(v1);
    REQUIRE(v1.size() == 2);
    std::vector<int> v2 { 2, 4};
    REQUIRE(v1 == v2);
}

TEST_CASE("vec-3") {
    std::vector<int> v1 { -1, 2, -3, 4, -5};
    REQUIRE(v1.size() == 5);

    erase_negatives_2020(v1);
    REQUIRE(v1.size() == 2);
    std::vector<int> v2 { 2, 4};
    REQUIRE(v1 == v2);
}