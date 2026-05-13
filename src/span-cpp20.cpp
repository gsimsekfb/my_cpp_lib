#include <array>
#include <cstddef>
#include <cstdio>
#include <span>
#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <algorithm>

#include "utils.h"

using namespace std;


// std::span (Rust slice)
// a non-owning view over a contiguous block of memory — lets you pass arrays,
// vectors, or raw pointers to functions without copying or caring about the 
// container type.

// before
void print(const std::vector<int>& vec);    // accepts only vector
void print(const int * arr, size_t n);      // accepts only raw ptr
void print(const std::array<int, 5>& arr);  // accepts only array

// now, cpp20 span
void print_span(std::span<const int> span) {      // accept all
    for (auto e : span) println(e);
}

// UB, not good
/* 
std::span<int> getSpan() {
    std::vector<int> v = {1, 2, 3};  // lives on stack
    return std::span(v);             // span points into v
} 
*/

TEST_CASE("span-1") {
    
    vector vec = {1, 2, 3};
    int arr[] = {1,2,3};
    std::array arr_ = {1,2,3};

    // 1. one function accepts all contiguous containers
    print_span(vec);
    print_span(arr);
    print_span(arr_);

    // 2. slicing / subspan
    auto first_two_elem = std::span(vec).first(2);
    // print_span(first_two_elem);
    REQUIRE( std::ranges::equal(first_two_elem, vector {1,2}) );

    auto last_two_elem = std::span(vec).subspan(1,2); // 2 elems from index 1
    print_span(last_two_elem);
    REQUIRE( std::ranges::equal(last_two_elem, vector {2,3}) );

}
