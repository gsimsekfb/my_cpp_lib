#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// 
// - Type traits are compile-time functions that query or transform type 
//   properties — living in <type_traits>.
//
// Key notes:
// - all in <type_traits>
// - _v suffix = value shorthand (C++17): is_integral_v<T>, before cpp17 is_integral<T>::value
// - _t suffix = type shorthand  (C++14): remove_const_t<T>, before cpp14 remove_const<T>::type
// - evaluated entirely at compile time — zero runtime cost
// - foundation of concepts, SFINAE, and generic programming
// - decay_t most commonly used — strips ref, const, array→pointer


////  what is type trait?

namespace std_ {

    template <typename T>
    struct is_trivially_copyable {
        static constexpr bool value = __is_trivially_copyable(T); 
            // Compiler intrinsic
    };

    // The variable template (official language feature name) shortcut (C++17)
    // better to say: compile-time template constant
    template <typename T>
    inline constexpr bool is_trivially_copyable_v = 
        is_trivially_copyable<T>::value;
}

TEST_CASE("type-trait-1") {

    static_assert(std::is_trivially_copyable_v<int>);

}


//// use in templates — enable/disable overloads
template<typename T>
void process(T val) {
    if constexpr (std::is_integral_v<T>)
        std::cout << "int: " << val;
    else if constexpr (std::is_floating_point_v<T>)
        std::cout << "float: " << val;
}


//// use with concepts (C++20)
template<typename T>
concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;


/// some of type traits:
/*
//// query — properties
std::is_constructible_v<T, Args...>  // can T be constructed with Args?
std::is_copy_constructible_v<T>      // has copy constructor?
std::is_move_constructible_v<T>      // has move constructor?
std::is_destructible_v<T>            // has accessible destructor?
std::is_abstract_v<T>                // has pure virtual?
std::is_polymorphic_v<T>             // has any virtual?

//// transform — modify types
std::remove_const_t<const int>       // int
std::remove_reference_t<int&>        // int
std::remove_pointer_t<int*>          // int
std::add_const_t<int>                // const int
std::add_pointer_t<int>              // int*
std::add_lvalue_reference_t<int>     // int&
std::decay_t<const int&>             // int — removes ref + const
std::underlying_type_t<MyEnum>       // int (or whatever underlying type)

//// query — is_*
std::is_integral_v<int>         // true
std::is_integral_v<double>      // false
std::is_pointer_v<int*>         // true
std::is_reference_v<int&>       // true
std::is_const_v<const int>      // true
std::is_same_v<int, int>        // true
std::is_same_v<int, double>     // false
std::is_base_of_v<Base, Derived>// true
std::is_convertible_v<int, double> // true
std::is_trivially_copyable_v<T> // true if safe to memcpy
*/

}