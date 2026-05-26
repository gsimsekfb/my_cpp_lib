#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-private-field"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// 
// - 
//
// Key notes:


TEST_CASE("inher-1") {

    //// prefer composition over inheritance for code reuse

    struct Logger { void log(const string& msg) { cout << msg; } };
    // ❌ inheritance for code reuse — wrong
    struct Server : Logger { void start() { log("starting"); } };
    // ✓ composition — correct
    struct Server_ {
        Logger logger;  // has-a, not is-a
        void start() { logger.log("starting"); }
    };


    //// basic — single inheritance
    struct Animal {
        std::string name;
        Animal(std::string n) : name(n) {}
        virtual void speak() { std::cout << "Animal\n"; }
        virtual ~Animal() {}  // always virtual destructor ✓
            // Without this, deleting a derived object through a base pointer 
            // only calls the base destructor — the derived destructor is 
            // skipped, causing resource leaks.
            // why not? Because without `virtual`, the destructor call is 
            // resolved at compile time based on the pointer type (`Base*`) 
            // — it calls `Base::~Base()` directly, skipping the derived 
            // class's destructor entirely.
    };

    // struct defaults to public inheritance, class defaults to private
    struct Dog : Animal { // equivalent to "struct Dog : public Animal"
        Dog(std::string n) : Animal(n) {} // must call base constructor
        // always use override in derived — catches typos at compile time
        void speak() override { 
            std::cout << "woof\n";
            // or
            // Animal::speak();        // explicit base call ✓
        }
    };

    Dog d("rex");
    d.speak();         // "woof" ✓
    d.name;            // "rex" — inherited ✓

    //// access specifiers
    struct Base {
        int pub  = 1;    // public
    protected:
        int prot = 2;    // accessible in derived, not outside
    private:
        int priv = 3;    // not accessible in derived
    };

    struct Derived : Base {
        void fn() {
            pub++;    // ✓
            prot++;   // ✓
            // priv++;   // ❌
        }
    };

    //// inheritance access modes  // pub->pub: Base's pub is pub in Der.  
// - public inheritance: IS-A relationship (Dog IS-A Animal)
    struct D1 : public    Base {}; // pub→pub, prot→prot (default, most common)
    struct D2 : protected Base {}; // pub→prot, prot→prot
// - private inheritance: implemented-in-terms-of (rarely needed)
    struct D3 : private   Base {}; // pub→priv, prot→priv


    //// - multiple inheritance: use with care — diamond problem
    struct Flyable { virtual void fly() {} };
    struct Swimmable { virtual void swim() {} };

    struct Duck : Animal, Flyable, Swimmable {
        void fly()   override { std::cout << "flap\n"; }
        void swim()  override { std::cout << "splash\n"; }
        void speak() override { std::cout << "quack\n"; }
    };


    //// diamond problem and solution: virtual inheritance - one shared Base
    struct A { int x = 0; };
    struct B : virtual A {};   // virtual ✓
    struct C : virtual A {};   // virtual ✓
    struct D : B, C {};        // one shared A ✓ — 
                               // !! without virtual: two A copies

    D d_;
    d_.x;      // ✓ UNambiguous — one A
    d_.B::x;   // ✓ explicit
    d_.C::x;   // same x ✓


    //// final — prevent inheritance
    struct Base_ final {};
    // struct Derived_ : Base_ {};   // ❌ compile error ✓


    //// abstract class — pure virtual - aka interface
    struct Shape {
        virtual double area()  = 0;   // must implement
        virtual double perim() = 0;   // must implement
        virtual ~Shape() {}
    };

    struct Circle : Shape {
        double r;
        double area()  override { return 3.14 * r * r; }
        double perim() override { return 2 * 3.14 * r; }
    };

    // Shape s;         // ❌ cannot instantiate abstract class
    Circle c;        // ✓

}

}