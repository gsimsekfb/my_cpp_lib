#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// static_cast
// - static_cast is the standard compile-time cast — checked by the compiler 
//   but no runtime verification.

//
// Key notes:
// - static_cast: checked at compile time only — wrong downcast = UB
// - prefer static_cast over C-style cast (int)x — more explicit, searchable
// - C-style cast tries static_cast then reinterpret_cast — too permissive
// - use dynamic_cast when unsure of actual type at runtime
// - use static_cast for numeric conversions — makes truncation explicit


TEST_CASE("stat-cas-1") {

    //// numeric conversions
    int    i = static_cast<int>(3.14);     // double → int, truncates to 3
    double d = static_cast<double>(7);     // int → double ✓
    float  f = static_cast<float>(3.14);   // double → float, precision loss


    //// upcast — derived to base (always safe)
    struct Animal {};
    struct Dog : Animal {};
    struct Cat : Animal {};

    Dog dog;
    Animal* a = static_cast<Animal*>(&dog);  // ✓ always safe — implicit anyway
    Animal* a_ = &dog;                       // same — implicit upcast ✓


    //// downcast — base to derived (!! unsafe — no runtime check)
    // !! use when 100% sure about the type
    Animal* anim = new Dog();
    Dog* dog_ = static_cast<Dog*>(anim);   // ✓ works if a is actually Dog
    Cat* cat = static_cast<Cat*>(anim);    // ❌ UB — no check, wrong type
        // use dynamic_cast for safe downcast ✓


    //// void* — common in C interop
    void* ptr = malloc(sizeof(int));
    int* p = static_cast<int*>(ptr);         // void* → int* ✓


    //// enum to int / int to enum
    enum class Color { Red, Green, Blue };
    int red = static_cast<int>(Color::Red);  // enum → int ✓
    REQUIRE(red == 0);
    Color c = static_cast<Color>(1);         // int → enum ✓


    //// remove const — use const_cast instead
    const int x = 42;
    int y = static_cast<int>(x); // ✓ copies value — does not remove const

}

}