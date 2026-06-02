#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// enums
// - 
//
// Key notes:
// - underlying types can be: 
//   Any integral type: 
// - bool, char, signed char, unsigned char
// - short, unsigned short
// - int, unsigned int
// - long, unsigned long
// - long long, unsigned long long


TEST_CASE("ttt-1") {

    //// plain enum — C style, leaks names into scope
    enum Color { Red, Green, Blue };
    // enum Status { Red, Ok };        // ❌ Red redefined — name collision

    int x = Red;                    // ✓ implicit int conversion — unsafe
    if (x == Green) {}              // ✓ compares int to int — no type check


    //// enum class — scoped, typed, safe (C++11)
    // - prefer enum class over plain enum — scoped, no implicit int conversion
    enum class Color_ { Red, Green, Blue };
    enum class Status { Active, Inactive };  // ✓ no collision

    Color_ c_ = Color_::Red;           // must qualify ✓
    // int x_ = Color_::Red;           // ❌ no implicit conversion ✓
    int x_ = static_cast<int>(Color::Red);   // ✓ explicit cast required


    //// underlying type — default int
    // - specify underlying type for ABI stability and memory control
    enum class Color__ : uint8_t  { Red, Green, Blue };  // saves memory
    enum class Flags : uint32_t { None=0, A=1, B=2 };    // explicit values
    enum       OldStyle : short { X, Y };  // plain enum with type


    //// explicit values
    enum class HttpStatus : int {
        Ok          = 200,
        NotFound    = 404,
        ServerError = 500
    };

    HttpStatus s = HttpStatus::Ok;
    static_cast<int>(s);            // 200 ✓


    //// std::to_underlying — C++23
    // - std::to_underlying (C++23) cleaner than static_cast<int>
    auto val = std::to_underlying(HttpStatus::Ok);   // 200 ✓
    auto val_ = static_cast<int>(HttpStatus::Ok);     // C++11 ✓


    //// check value validity
    bool valid = (s == HttpStatus::Ok       ||
                  s == HttpStatus::NotFound ||
                  s == HttpStatus::ServerError);

    //// switch
    switch (s) {
        using enum HttpStatus;        // C++20 — drop prefix ✓
        case Ok:          break;
        case NotFound:    break;
        case ServerError: break;
    }


    //// iterate — no built-in, common workaround
    enum class Dir { North, South, East, West, COUNT };

    for (int i = 0; i < static_cast<int>(Dir::COUNT); ++i) {
        Dir d = static_cast<Dir>(i);
    }


    //// bitflags — plain enum or uint
    enum Perms : uint32_t {
        None    = 0,
        Read    = 1 << 0,   // 0001
        Write   = 1 << 1,   // 0010
        Execute = 1 << 2,   // 0100
    };

    uint32_t p = Read | Write;      // ✓
    bool canRead = p & Read;        // ✓


    //// forward declare enum class
    enum class Color1 : int;         // ✓ must specify underlying type
    void fn(Color1 c);               // use before definition ✓


}

}