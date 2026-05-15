#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;


TEST_CASE("stu-bin-1") {

    // pair / tuple
    auto [a, b] = std::make_pair(1, 2.5);
    auto [aa, _, cc] = std::make_tuple(1, "hi", 3.0);

    // struct unpacking
    struct Point { int x, y, z; };
    Point p {1, 2, 3};
    auto [x, y, z] = p;

    // map iteration — most common use
    map<string, int> scores = { {"alex", 10}, {"bob", 20} };  
    for (const auto& [name, score] : scores)
        std::cout << std::format("{}: {}\n", name, score);

    // array unpacking
    int arr[3] = {1, 2, 3};
    auto& [xx, yy, zz] = arr;
    xx = 42;
    REQUIRE(arr[0] == 42);

    // vector vec = { 1,2,3 };
    // auto [f, ff, fff] = vec;
        // error: std::vector doesn't support structured bindings since its 
        // size is runtime-determined, not compile-time.

    // function returning multiple values
    // auto [id, name, active] = getUser();}

}