#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <string>
#include <span>

#include "utils.h"

using std::string;
/* 
                     owned   mutable   sized   allocated    version  rust_eq
------------------------------------------------------------------------------
std::string           ✓       ✓         ✓       heap        C++98    String
std::string_view      ✗       ✗         ✓       none        C++17    &str
const char*           ✗       ✗         ✗       none        C        *const char*                 ✗       ✓         ✗       none        C        *mut u8
char[N]               ✓       ✓         ✓       stack       C        [u8; N]
std::array<char,N>    ✓       ✓         ✓       stack       C++11    [u8; N]
std::vector<char>     ✓       ✓         ✓       heap        C++98    Vec<u8>
std::span<char>       ✗       ✓         ✓       none        C++20    &mut [u8]
std::span<const char> ✗       ✗         ✓       none        C++20    &[u8]
------------------------------------------------------------------------------
*/

TEST_CASE("st-1") {

    //// std::string — owning, mutable, heap allocated  |  Rust: String
    std::string str = "hello";
    str += " world";              // mutable ✓
    str.size();                   // has size ✓
        // owns data, freed on destruction


    //// std::string_view — non-owning, read-only, no allocation  |  Rust: &str
    std::string_view str_view_ = "hello";
    std::string_view str_view = str;    // view into existing string — no copy ✓
    str_view.size();                  // has size ✓
    str_view[0];                      // read only
        // danger: must not outlive source string


    //// const char* — C-style, non-owning, no size  |  Rust: *const c_char
    const char* str__ = "hello";    // string literal — read-only memory
    REQUIRE(strlen(str__) == 5);    // no .size() — must call strlen ❌
        // no bounds checking, no size, null-terminated only


    //// char* — C-style, mutable, no size  |  Rust: *mut c_char
    char buf_[] = "hello";
    char* str2 = buf_;
    str2[0] = 'H';                 // mutable ✓
        // danger: no size, manual memory, no bounds check


    //// char[N] — fixed size, stack, mutable  |  Rust: [u8; N]
    char buf__[6] = "hello";      // fixed at compile time
    buf__[0] = 'H';               // mutable ✓
    sizeof(buf__);                 // 6 — size known ✓
        // not null-terminated unless you add '\0' manually


    //// std::array<char, N> — fixed size, stack, mutable  |  Rust: [u8; N]
    std::array<char, 6> buf = {'h','e','l','l','o','\0'};
    buf[0] = 'H';               // mutable ✓
    buf.size();                  // 6 ✓
        // safer than char[] — has iterators, size(), no pointer decay

    //// std::vector<char> — owning, mutable, dynamic  |  Rust: Vec<u8>
    std::vector<char> buf_1 = {'h','e','l','l','o'};
    buf_1.push_back('!');         // dynamic size ✓
    buf_1.size();                  // has size ✓
        // use for binary buffers — not null-terminated


    //// std::span<const char> — non-owning, read-only view  |  Rust: &[u8]
    std::span<const char> slice(buf.data(), buf.size());
    slice.size();                  // has size ✓
        // read only, no allocation, must not outlive source


    //// std::span<char> — non-owning, mutable view  |  Rust: &mut [u8]
    std::span<char> slice_(buf.data(), buf.size());
    slice_[0] = 'H';               // mutable view ✓
        // no allocation, must not outlive source

}
