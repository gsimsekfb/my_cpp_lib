#include <variant>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

//// union — all members share same memory, one active at a time
//
// Key notes:
// C++ Core Guidelines:
// In short: avoid bare unions, prefer `std::variant` (C++17) or
// std::bit_cast` for type punning.


TEST_CASE("uni-1") {

    //// union — all members share same memory, one active at a time
    union Value {
        int    i;
        float  f;
        double d;     // largest — determines size
    };

    sizeof(Value);    // sizeof(double) ✓

    // only one member active at a time — reading inactive = UB
    Value v;
    v.i = 42;        // i is now active
    // v.f;             // ❌ UB — i is active, not f


    //// prefer std::variant over raw union
    std::variant<int, float, std::string> var = 42;  // type-safe ✓


    //// anonymous union — members accessed directly
    struct Packet {
        int type;
        union {
            int   intVal;
            float floatVal;
        };             // no name — accessed directly ✓
    };

    Packet p;
    p.intVal   = 42;
    p.floatVal = 3.14f;


    //// tagged union - Pre-C++17 equivalent to a Rust enum
    struct IpAddr {
        enum Type { V4, V6 } type; // The "tag" to know which variant is active

        union {
            uint32_t v4_addr;
            std::string v6_addr; 
                // Unrestricted union (C++11), requires manual lifetime
                // management
        };

        // Ctors and Dtor required to safely handle the string lifetime
        // why: compiler will not automatically create/destroy those objects 
        // because it does not know which union member is currently active
        IpAddr(uint32_t ip) : type(V4), v4_addr(ip) {}
        IpAddr(std::string ip) : type(V6), v6_addr(std::move(ip)) {}
        ~IpAddr() { if (type == V6) v6_addr.~basic_string(); }
    };


    //// tagged union-2
    struct Value_ {
        enum class Type { Int, Float } type;
        union {
            int   i;
            float f;
        };

        void set(int   x) { i = x; type = Type::Int;   }
        void set(float x) { f = x; type = Type::Float; }

        void print() {
            if (type == Type::Int)   std::cout << i;
            else                     std::cout << f;
        }
    };


    //// type punning — use std::bit_cast (C++20) not union
    float f = 3.14f;
    uint32_t bits = std::bit_cast<uint32_t>(f);   // ✓ safe
    
    // union type punning = UB in C++ ❌
    union Pun {
        float floatVal;
        uint32_t intVal;
    };

    Pun pun;
    pun.floatVal = 3.14f;
    uint32_t bits_ = pun.intVal;  
        // ❌ UB — reading inactive member (i was never written)


}

}