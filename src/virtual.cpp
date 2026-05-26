#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// virtual
// - enables runtime polymorphism — the correct function is called based 
//   on the actual object type, not the pointer/reference type.
//
// Key notes:
// - always declare virtual dtor in base class with virtual functions
// - always use override in derived — catches base class changes at compile time
// - final on class: struct Dog final : Animal {} — whole class non-derivable
// - pure virtual (=0) makes class abstract — cannot be instantiated
// - virtual has runtime cost: vtable pointer per object + indirect call
// - non-virtual functions are resolved at compile time — no cost
//
// vtable — how it works
// each class with virtual functions has a vtable (array of fn pointers)
// each object has a vptr pointing to its class vtable
// virtual call = follow vptr → lookup in vtable → call ✓
// cost: one pointer per object + one indirection per virtual call


TEST_CASE("virtual-1") {

    //// 1. virtual methods
    // without virtual — wrong function called
    struct Animal {
        string_view speak() { return "Animal"; }
    };
    struct Dog : Animal {
        string_view speak() { return "Dog"; }
    };

    Animal* dog = new Dog();
    dog->speak();   // "..." — calls Animal::speak ❌ wrong
    REQUIRE(dog->speak() == "Animal");  // Bad, should be Dog

    // with virtual — correct function called
    struct Animal_ {
        virtual string_view speak() { return "Animal"; }
    };
    struct Dog_ : Animal_ {
        string_view speak() override { return "Dog"; }
    };

    Animal_* dog_ = new Dog_();
    dog_->speak();   // "woof" — calls Dog::speak ✓
    REQUIRE(dog_->speak() == "Dog");  // Good


    //// 2. override — C++11, catches typos at compile time
    struct Animal__ { virtual void speak() { } };
    struct Dog__ : Animal__ {
        // void speak_() override {} 
            // ❌ compile error — no base virtual speak_() ✓
        void speak() override {} // OK
    };


    {
    
    //// 3. final — prevent further override (C++11)
    struct Animal { virtual void speak() { } };
    struct Dog : Animal {
        void speak() override final {}  // no derived class can override ✓
    };

    struct Poodle : Dog {
        // void speak() override {}   // ❌ compile error — speak() is final
    };


    //// 4. pure virtual — abstract class
    struct Animal_ {
        virtual void speak() = 0;  // must be overridden — no default impl
        virtual ~Animal_() {}
    };

    // Animal_ animal;         // ❌ cannot instantiate abstract class
    struct Dog_ : Animal_ {
        void speak() override { }  // ✓ must implement
    };


    //// 5. virtual dtor — always needed with polymorphism
    struct Animal__ {
        virtual ~Animal__() {}   // ✓ ensures derived destructor called
    };
    struct Dog__ : Animal__ {
        ~Dog__() { } // dtor
    };

    Animal__* dog = new Dog__();
    delete dog;   // without virtual ~Animal: only ~Animal called — leak ❌
                  // with    virtual ~Animal: ~Dog then ~Animal called ✓

    }

}

}