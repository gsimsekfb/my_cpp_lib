#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()

#include "utils.h"

using namespace std;

namespace {

// what affects overloading:
// -----------------------------------------------------
// parameter count          f()      vs   f(int)
// parameter types          f(int)   vs   f(double)
// const/ref qualifiers     f(int&)  vs   f(const int&)
// rvalue/lvalue ref        f(int&)  vs   f(int&&)
// pointer vs value         f(int)   vs   f(int*)
//
// does NOT affect:
// -----------------------------------------------------
// return type only
// const on value params:
//   f(int) == f(const int)
//   f(string) == f(const string)

}