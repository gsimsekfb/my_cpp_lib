#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// std::variant 
// - variant == Rust enum 
// - a type-safe union — holds exactly one of a fixed set of types. 
// - enum vs variant: C++ enum is just named integers; `std::variant` is a 
//   "type-safe" tagged union that can hold different types with actual values
//   closer to Rust enums.
//
// Key notes:
// - Fixed set of types known at compile time — type-safe, no heap allocation
// - Always holds exactly one type — never empty (unless std::monostate added)
// - get<T> throws; get_if<T> returns nullptr — prefer get_if for safety
// - std::visit forces you to handle all types — like Rust match
// - Use for: error handling (variant<Result, Error>), state machines, AST nodes

// std::any 
// - holds a value of any type with type erasure.
// - any → Rust Box<dyn Any> (from std::any::Any).
//
// Key notes:
// - Any type at runtime — uses heap allocation for large types
// - No compile-time type info — checked at runtime only
// - Slower and less safe than variant — only use when types truly unknown at
//   compile time
// - Use for: plugin systems, config values, type-erased containers

#include <variant>

//// 1. simple usage

TEST_CASE("var-any-1") {
    // define
    std::variant<int, double, std::string> var;

    var = 42;          // holds int
    var = 3.14;        // now holds double
    var = "hello";     // now holds string

    // check which type is active
    std::holds_alternative<int>(var);         // false
    std::holds_alternative<std::string>(var); // true

    // access — throws if wrong type
    std::get<std::string>(var);  // "hello" ✓
    // std::get<int>(var);       // ❌ throws std::bad_variant_access

    // safe access — returns nullptr if wrong type
    if (auto* p = std::get_if<std::string>(&var))
        std::cout << *p << "\n";
}


//// 2. Return Result/Error from fns like in Rust

struct Result { int x; };
enum Error { SEG_FAULT, INVALID_ID };

std::variant<Result, Error> foo(int x) {
    if (x == 42) return Result {99};
    return Error::INVALID_ID; 
}

// helper
template<typename... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

TEST_CASE("var-any-2") {

    auto var = foo(422);

    // exhaustiveness match
    std::visit(overloaded {
        [](const Result& res) { std::cout << res.x << "\n" ; },
        [](const Error& err) { std::cout << err << "\n"; }
    }, var);

}

//// 3. IpAddr variant example

/* Rust
    enum IpAddr {
        V4(u8, u8, u8, u8),
        V6(String),
    }
*/

struct IPV4 { uint16_t x, y, z, t; };
struct IPV6 { string addr; };

using IpAddr = std::variant<IPV4, IPV6>;

TEST_CASE("var-any-3") {

    IpAddr ip4 = IPV4 { 192,1,1,1 };
    IpAddr ip6 = IPV6 { "some-addr" };

    // !! exhaustiveness match
    //    e.g. add IPV8 -> IpAddr = std::variant<IPV4, IPV6, IPV8>; 
    //    and visit will error at compile time
    IpAddr res = std::visit(overloaded {
        [](const IPV4& addr) -> IpAddr { return addr; },
        [](const IPV6& addr) -> IpAddr { return addr; }
    }, ip4);


    // safe access — returns nullptr if wrong type
    if (IPV4* val = std::get_if<IPV4>(&res))
        REQUIRE(val->x == 192);

}


//// 4. std::any

#include <any>

TEST_CASE("var-any-4") {

    std::any my_any = 42;
    my_any = 3.14;
    my_any = std::vector<int>{1,2,3};   // any type ✓
    my_any = std::string("hello");

    // check type
    my_any.type() == typeid(std::string);  // true
    my_any.has_value();                    // true

    // access — throws std::bad_any_cast if wrong type
    auto str = std::any_cast<std::string>(my_any);   // ✓
    // auto i = std::any_cast<int>(my_any);        // ❌ throws

    // safe cast — returns nullptr if wrong type
    if (auto* val = std::any_cast<std::string>(&my_any))
        REQUIRE(*val == "hello");

    my_any.reset();   // clear — now empty
    REQUIRE(my_any.has_value() == false);
}

