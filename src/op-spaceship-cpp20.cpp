#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;


// operator<=> (the "spaceship operator") 
// auto-generates all 6 comparison operators: <, >, <=, >=, ==, != 
// from a single definition.
// 
// The most important practical win: 
// any type with "operator<=> = default" instantly works as a std::map key 
// or in std::sort with zero extra code.

//// 1. Default impl.
// now
struct Point {
    int x, y;
    auto operator<=>(const Point&) const = default; // **
};

// before
struct Point_ {
    int x, y;
    bool operator==(const Point_& o) const { return x==o.x && y==o.y; }
    bool operator< (const Point_& o) const { 
        return x<o.x || (x==o.x && y<o.y); 
    }
    bool operator> (const Point_& o) const { return o < *this; }
    bool operator<=(const Point_& o) const { return !(o < *this); }
    bool operator>=(const Point_& o) const { return !(*this < o); }
    bool operator!=(const Point_& o) const { return !(*this == o); }
};

TEST_CASE("op-space-1") {
    Point a {1,2}, b {2,3};
    REQUIRE(a != b);
    
    Point_ c {1,2}, d {2,3};
    REQUIRE(c != d);
}


//// 2. Custom impl. of operator<=> 
struct Person {
    string name;
    int age;

    // ** sort by age only, ignore name
    auto operator<=>(const Person& rhs) const {
        return age <=> rhs.age;
    }

    // Note: When we provide a custom operator<=>, the compiler no longer 
    // auto-generates ==, so we must define it explicitly
    bool operator==(const Person& rhs) const {
        return age == rhs.age;
    }
};

TEST_CASE("op-space-2") {
    Person a {"aa", 5}, b {"bb", 10};
    REQUIRE(a != b);
}
