#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <string_view>
#include "utils.h"

using namespace std;

// string_view
// - string_view is a non-owning, read-only view over any string data — no 
//   allocation, no copy.
// - fat ptr (ptr + len) same as Rust &str
//
// Key notes:
// - Non-owning — does NOT copy or allocate
// - Read-only — no modification of underlying data
// - Prefer over const string& for fn params — works on all string types
// - Danger: never return string_view of a local string — dangling view
// - Danger: string_view does not null-terminate — don't pass to C APIs 
//   expecting char*
// - C++20 adds starts_with / ends_with
// - Converting to std::string forces a copy: std::string s(sv)


//// 1. basic usage — accepts any string type without copying
void foo(std::string_view sv) {
    std::cout << sv << "\n";
}

TEST_CASE("str-view-1") {

    //// 1. contd.

    foo("hello");             // ✓ string literal
    foo(std::string("hi"));   // ✓ std::string
    char buf[] = "abc"; // mut array on stack, value copied from literal
       // or
        const char* buf_ = "abc"; // read only ptr to literal in static mem.
    foo(string_view(buf, 5)); // ✓ raw char* + length


    //// 2. 
    // string -> string_view
    string str = "hello";
    string_view sv_ = str; // no copy

    // string_view -> string
    string_view sv__ = "hello";
    string str_ = string(sv__);  // force copy
    // string str_ = sv__;       // implicit


    //// 3. other use cases

    // substr — no allocation (just moves pointer+length)
    std::string_view sv = "hello world";
    sv.substr(6, 5);            // "world" — zero copy ✓

    // starts_with / ends_with (C++20)
    sv.starts_with("hello");    // true
    sv.ends_with("world");      // true

    // trimming — adjust view without copying
    sv.remove_prefix(2);        // skip first 2 chars
    sv.remove_suffix(2);        // skip last 2 chars

}
