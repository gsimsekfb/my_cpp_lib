#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"


TEST_CASE("ctad-1") {

    //// class template argument deduction
    
    // before C++17 — must specify explicitly
    std::pair<int, double> p(1, 2.5);
    std::vector<int> v = {1, 2, 3};

    // now, CTAD — deduced from constructor args
    std::pair pp(1, 2.5);          // pair<int, double> ✓
    std::vector vv = {1, 2, 3};   // vector<int> ✓
    std::tuple tt(1, "hi", 3.0);  // tuple<int, const char*, double> ✓

}
