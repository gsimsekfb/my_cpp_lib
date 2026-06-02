#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <ranges>

#include "utils.h"

using namespace std;

// ranges
// - std::ranges is a modernized algorithm library that works directly on 
//   containers (no more .begin()/.end()), and supports lazy views that chain 
//   operations without allocating.
//
// Key notes:
// - Two parts: range algorithms (std::ranges::sort etc.) and view 
//   (std::views::)
// - Views are lazy — nothing executes until you iterate
// - Views don't allocate — no intermediate containers
// - Pipe operator | chains views left to right, reads like a pipeline
// - views::iota replaces manual index generation (e.g. Rust [0..5])
// - views are non-owning — don't let them outlive their source range

TEST_CASE("ranges-1") {

    std::vector<int> vec = {3,1,4,1,5,9};

    //// 1. ranges — pass container directly

    // cpp20
    ranges::sort(vec);                // no .begin()/.end()
    auto itr = ranges::find(vec, 4);  // cleaner
    // before
    std::sort(vec.begin(), vec.end());
    auto itr_ = std::find(vec.begin(), vec.end(), 4);


    //// 2. views - lazy, chainable, zero allocation

    /// filter, square them, take first 3
    namespace views = std::views;
    auto view = vec
        | views::filter([](int x){ return x < 4; })
        | views::transform([](int x){ return x * x; })
        | views::take(3);
        // type of `view`: lazy nested view type:    
        // take_view<transform_view<filter_view<ref_view<vector<int>>>>>
    /// materialize view into vector
    // cpp20
    auto view_ = view | views::common;
    vector result_vec (view_.begin(), view_.end());
    REQUIRE(result_vec == vector {1,1,9});
    // cpp23 std::ranges::to<T> - Rust: .collect::<T>()
    auto result_vec_ = view | std::ranges::to<std::vector>();
    print_type(result_vec_); // std::vector<int,class std::allocator<int> >
    REQUIRE(result_vec_ == vector {1,1,9});

    /// common views
        // views::filter(pred)       // keep elements matching predicate
        // views::transform(fn)      // apply fn to each element
        // views::take(n)            // first n elements
        // views::drop(n)            // skip first n elements
        // views::reverse            // iterate backwards
        // views::keys               // keys of a map
        // views::values             // values of a map
        // views::iota(0, 10)        // generate 0,1,2...9
        // views::split(str, delim)  // split string


    //// 3. More practical uses

    // a. iterate over map keys/values
    std::map<string, int> scores = { {"alice",95},{"bob",80},{"carol",90} };

    for (auto& name  : scores | views::keys)   std::cout << name  << "\n";
    for (auto& score : scores | views::values) std::cout << score << "\n";
    // or
    for (auto& [key, val] : scores) { print(key); print(":"); println(val); };

    // b. iota — generate sequence

    // replaces hand-written index loops
    for (int i : views::iota(0, 5))
        std::cout << i << "\n";  // 0 1 2 3 4

    // combine with transform
    auto squares = views::iota(1, 6)
                   | views::transform([](int x){ return x*x; });
    // 1 4 9 16 25 — no vector created ✓
}

