#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-result"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <map>
#include <ranges>
#include "utils.h"

using namespace std;


/* map & set
C++                       Rust:
------------------------------------------------------------
- map/set               → BTreeMap (ordered, unique, tree)
- unordered_map/_set    → HashMap  (unordered, unique, hash)
- *multimap/multiset    → no direct eq. in Rust (ordered, multi-key, tree)
  (*multimap: map that allows same keys; elems with same key ordered by 
    insertion order)
*/

//// choose which
// map            — ordered iteration needed, O(log n)
// unordered_map  — "fastest lookup", no ordering needed, O(1) avg
// multimap       — duplicate keys needed
// set            — ordered unique values, membership test
// unordered_set  — "fastest" membership test, no ordering needed
// multiset       — duplicate values, ordered
// flat_map/set   — small collections, cache-friendly (C++23)
//
//// std::flat_map and std::flat_set cpp23
// - sorted vector-backed associative containers — same interface as map/set b/
//   but cache-friendly contiguous memory.
//
// flat_map vs map
// std::map: pointer-based tree, O(log n), pointer per node, cache unfriendly
// std::flat_map: sorted vector, O(log n), contiguous memory, cache friendly
// flat_map faster: lookup, iteration (cache), small collections
// map faster:      insert/erase in middle of large collections
// - best for: read-heavy, small-medium size, built once then queried
// - worst for: frequent insert/erase in large collections — use map


//// key notes
// - operator[] on map creates default value if key missing — use at() or find()
// - unordered_map is faster on average but worst case O(n) — hash collisions
// - map/set iterators are stable — not invalidated by insert/erase of other elements
// - unordered_map iterators invalidated on rehash — don't store them
    // Yes — same concept, different trigger: vector doubles when size 
    // reaches capacity, unordered_map rehashes when size/buckets ratio 
    // exceeds the load factor threshold.
// - contains() is C++20 — use find() != end() for C++17 and earlier
// - emplace() always preferred over insert() — no temporary created


TEST_CASE("map-1") {

    ///// 1. map — ordered, unique keys, O(log n)
    std::map<std::string, int> map;

    //// access
    map["key"];                        // !! creates default if not exists !!
    map.at("key");                     // throws if not exists ✓
    map.contains("key");               // C++20 — bool ✓
    map.find("key") != map.end();      // C++11 check

    //// insert
    map["key"] = 42;                 // operator[] — inserts if not exists 
    map.insert({"key", 42});         // insert pair
    map.insert_or_assign("key", 42); // insert or overwrite (C++17)
    map.emplace("key", 42);          // construct in-place ✓
    // if init statement cpp17
    if (auto [it, ok] = map.insert({"z", 1}); ok)
        std::cout << "inserted\n";   // structured binding in init ✓


    //// iterate
    // cpp17
    for (const auto& [k, v] : map) {} // structured binding ✓
    // C++23 — views
    // for (auto& [k, v] : map | std::views::filter([](){}))
        // std::cout << k << ": " << v;

    //// iterate & erase
    // cpp20
    std::erase_if(map, [](const auto& pair) { return pair.second < 0; } );

    // pre-cpp11
    for(auto it = map.begin(); it != map.end(); ) {
        if(it->first.starts_with("a")) 
            it = map.erase(it); // erase already iterates to next elem.
        else
            ++it;
    }


    //// erase
    map.erase("key");              // erase by key
    // erase by iter
    if (auto it = map.find("key2"); it != map.end())
        map.erase(it);


    //// 2. unordered_map — hash map, unique keys, O(1) avg
    std::unordered_map<std::string, int> map2;
        // same API as map — but no ordering, faster average case

    //// reserve buckets — avoid rehashing
    map2.reserve(1000);                        // ✓ perf optimization


    //// 3. set — ordered, unique values, O(log n)
    std::set<int> s {1, 2, 3};
    s.insert(4);
    s.contains(3);                          // C++20 ✓
    s.erase(2);
    s.find(3) != s.end();                   // C++11

}