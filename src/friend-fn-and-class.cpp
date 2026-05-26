#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// 
// - friend grants a function or class access to private and protected members 
//   — breaking encapsulation deliberately.
//   e.g. Operator << must be a non-member, but needs private access
//
// Key notes:
// - friend declaration is always in the class granting access
// - alternative: provide public getters instead of friend


//// - most common use: operator overloading (<<, +, ==)
//// friend function defined inside class
struct Vec {
    float x, y;

    friend Vec operator+(const Vec& a, const Vec& b) {
        return {a.x + b.x, a.y + b.y};   // ✓ access private x, y
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec& v) {
        return os << v.x << ", " << v.y;  // ✓
    }
};

// Vec2 a{1,2}, b{3,4};
// Vec2 c = a + b;             // ✓
// std::cout << c;             // ✓


//// friend function — access private members
struct BankAccount {
    friend void audit(const BankAccount& a);  // declaration ✓
private:
    double balance = 1000.0;
};

void audit(const BankAccount& a) {
    std::cout << a.balance;   // ✓ private access via friend
}


//// friend class — all methods get access
struct Engine;

struct Car {
    friend struct Engine;   // Engine can access Car's private members
private:
    int horsepower = 300;
};

struct Engine {
    void tune(Car& c) {
        c.horsepower += 50;  // ✓ private access
    }
};


//// friend is not inherited
struct Base {
    friend struct Foo;       // Foo can access Base's private
private:
    int x;
};

struct Derived : Base {
    int y;
};

struct Foo {
    void fn(Base& b, Derived& d) {
        b.x;   // ✓ friend of Base
        d.x;   // ✓ inherited member — still Base's x
        // d.y;   // ❌ NOT friend of Derived
    }
};


//// friend is not transitive
// A friends B, B friends C → C cannot access A's private ❌


}