#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// import std; 
// - introduces named modules to the C++ Standard Library, allowing you to
//   import the entire standard library as a single, pre-compiled module
//   instead of using the preprocessor to textually include header files.
//
// Key notes:


//// Major Reasons Added
// The primary reason for adding import std; is to eliminate the massive 
// compilation bottleneck caused by the preprocessor repeatedly parsing 
// hundreds of thousands of lines of code in traditional header files.

// TRADITIONAL (Slow): Preprocessor copies and pastes thousands of lines for 
// each header:
#include <iostream>
#include <vector>

// C++23 MODULES (Fast): Compiled once into a binary format, then imported 
// instantly':
// import std;
/* 
int main() {
    std::vector<int> nums = {1, 2, 3};
    std::print("{}\n", nums.size()); // std::print is also new in C++23
}
*/


//// Use Case: Rapid prototyping and clean code w/o managing a dozen #includes
/* 
import std;

int main() {
    // Mixes strings, containers, algorithms, and I/O seamlessly without header bloat
    std::string text = "hello modules";
    std::ranges::reverse(text);
    std::cout << text << '\n'; 
}
*/


}