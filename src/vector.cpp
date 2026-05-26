#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-result"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <algorithm>

#include "utils.h"

namespace {

using namespace std;

// vector
// - dynamic array, contiguous memory, O(1) random access
//
// Key notes:
// - contiguous memory — cache friendly, best default container
// - push_back may reallocate — invalidates all iterators
// - reserve() before bulk inserts — avoid repeated reallocation ✓
// - emplace_back() over push_back() — constructs in-place, no temp
// - operator[] no bounds check — use at() during development
// - prefer std::erase / std::erase_if over erase-remove idiom (C++20)


TEST_CASE("vec-0") {

    //// create
    std::vector<int> v4;                    // empty
    std::vector<int> v3 (5);                // 5 zeros - !! cannot use {} init
    std::vector<int> v2 (3, 42);            // {42,42,42} - !! cannot use {}
    std::vector<int> v1 {1, 2, 3, 4, 5};    // initializer list
    std::vector<int> vec { v1.begin(), v1.end() }; // from range
    //// 2D vector
    vector<vector<int>> grid(3, std::vector<int>(4, 0)); // 3x4 zeros

    REQUIRE(v3 == std::vector {0,0,0,0,0});
    REQUIRE(v2 == std::vector {42,42,42});

    //// access
    vec[0];       // !! no bounds check — UB if out of range
    // vec.at(0);    // bounds checked — throws ✓
    vec.front();  // first element
    vec.back();   // last element
    int* dataPtr = vec.data();   // raw pointer to buffer
    REQUIRE(*dataPtr == 1);


    //// insert
    vec.push_back(42);                    // append — copy
    // perf. emplace_back:
    std::vector<std::string> v;
    v.push_back("hello");           // creates temporary string, then moves
    v.emplace_back("hello");        // constructs string directly in-place ✓
    // and for Foo {"bob", 42}
    // vec.emplace_back("bob", 42)        // construct in-place — prefer ✓
        // for ctors, use emplace_back() instead of push_back()
        // vec.push_back(Foo {"bob", 42});
    int val = 42;
    vec.push_back(std::move(val));           // append — move ✓
    vec.insert(vec.begin(), 42);             // insert at position — O(n)
    vec.insert(vec.begin() + 2, 42);         // insert at index 2


    //// remove
    vec.pop_back();                           // remove last — O(1)
    vec.erase(vec.begin());                   // remove first — O(n)
        // !! erase vec.end() = UB
    vec.erase(vec.begin() + 2);               // remove at index — O(n)
    vec.erase(vec.begin(), vec.begin() + 3);  // remove range
    std::erase(vec, 42);                      // remove all 42s — C++20 ✓

    // cpp20
    std::erase_if(vec, [](int e) { return e < 0; } );
    // cpp11 - erase-remove idiom
    vec.erase(
        std::remove_if( vec.begin(), vec.end(), [](int e ) { return e < 0; } ),
        vec.end()
    );
    // pre-cpp11
    for (auto it = vec.begin(); it != vec.end();) {
        if (*it < 0)
            it = vec.erase(it); // !! iter invalidation risk
                // the risk: erase invalidates all iterators after the erased 
                // position, but since erase returns the next valid iterator 
                // and we assign it back to it, this specific code is actually 
                // safe.
        else
            ++it;
    }

    //// iterate
    for (const auto& x : vec) {}               // range-for  - cpp11
    for (size_t i = 0; i < vec.size(); i++) {} // index      - cpp98
    for (auto it = vec.begin(); it != vec.end(); ++it) {} // - cpp11

    //// size / capacity
    vec.size();                  // number of elements
    vec.capacity();              // allocated slots
    vec.resize(10);              // grow/shrink — new elements zero-init
    vec.resize(10, 99);          // grow with value
    vec.reserve(1000);           // perf: pre-allocate — avoid rehashing ✓
    for (int i = 0; i < 1000; ++i)
        vec.push_back(i);  // no reallocation — buffer pre-allocated

    vec.shrink_to_fit();         // release excess memory
        // reduces capacity() to match size() — useful after many erases to 
        // free unused reserved memory; it's a non-binding hint (compiler may 
        // ignore it).


    //// clear
    vec.clear();  // size = 0, capacity unchanged
    vec = {};     // size = 0, capacity unchanged


    //// algorithms
    std::ranges::find(vec, 42);             // C++20 ✓
    std::ranges::find_if(vec, [](int x){ return x > 3; });
    // cpp11, due to lambda is cpp11
    std::find_if(vec.begin(), vec.end(), [](int x){ return x > 3; }); 
    std::find(vec.begin(), vec.end(), 42); // cpp98

    std::ranges::sort(vec);                // C++20 ✓
    std::sort(vec.begin(), vec.end());     // cpp98


    //// copy / move
    std::vector<int> v7 { vec }; // copy ctor
    std::vector<int> v5 = vec;   // copt ctor
    auto v6 = std::move(vec);    // move ctor — v now empty ✓

}

}
