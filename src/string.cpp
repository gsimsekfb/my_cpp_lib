#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <string>

#include "utils.h"

using std::string;

TEST_CASE("st-1") {
    string str { "aa" };
    auto len = str.size();  // string size: 2
    REQUIRE(len == 2);

    // C array
    char arr[] {"abc"};
    auto len2 = std::size(arr); // array size: 4
    REQUIRE(len2 == 4);

    // C string
    const char* arr3 = "abc";
    auto len3 = std::strlen(arr3);  // str len: 3
    REQUIRE(len3 == 3);
}
