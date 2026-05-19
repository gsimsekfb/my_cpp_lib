// #pragma once
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

namespace {

using namespace std;

// Variadic templates
// - accept any number of template parameters of any types 
// - the foundation of std::tuple, std::make_shared, and perfect forwarding.
//
// Key notes:
// - typename... Args = parameter pack (types)
// - Args...  args    = pack expansion
// - sizeof...(Args)  = count at compile time
// - ... placement matters — Args... expands the pack
// - C++11: recursion to process pack; C++17: fold expressions (prefer)
// - foundation of: tuple, make_shared, make_unique, std::invoke, std::apply


//// basic — accept any number/type of args
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args);   // fold expression (C++17) ✓
}
// print(1, " ", 3.14, " ", "hi");  // ✓ any types, any count


//// sizeof... — count params
template<typename... Args>
void countArgs(Args... args) {
    std::cout << sizeof...(args);  // number of args ✓
    std::cout << sizeof...(Args);  // number of types ✓
}

//// perfect forwarding — most important use case
template<typename T, typename... Args>
std::unique_ptr<T> make(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
// this IS how make_unique is implemented ✓


//// variadic class template — how tuple works
template<typename... Types>
struct Tuple {};


TEST_CASE("var-tem-1") {

    // variadic generic lambda
    auto printAll = [](auto... args) {
        (std::cout << ... << args);   // fold expression ✓
    };

    printAll(1, " ", 3.14, " ", "hi");

    printAll(1, " ", 3.14);



}

}
