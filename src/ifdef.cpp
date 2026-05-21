#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// #ifdef & #if
// - 
//
// Key notes:
// - prefer #pragma once over include guards — less error prone
// - #ifdef checks if macro is defined — not its value
// - #if checks the value — #if MAX_USERS > 100
// - constexpr and if constexpr preferred over macros in modern C++
// - macros have no scope, no type — avoid for constants and functions


//// include guard — prevent header included multiple times
// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H
// ... header content ...
#endif


//// pragma once — same effect, simpler (non-standard but universally supported)
// #pragma once
// ... header content ...


//// conditional compilation — platform
#ifdef _WIN32
    // #include <windows.h>
#elif defined(__linux__)
    // #include <unistd.h>
#elif defined(__APPLE__)
    // #include <TargetConditionals.h>
#endif


//// conditional compilation — debug vs release
#ifdef NDEBUG
    // release build
#else
    // debug build
#endif

#ifdef DEBUG
    std::cout << "debug: " << val << "\n";
#endif


//// define from command line
// g++ -DDEBUG main.cpp
// g++ -DMAX_USERS=100 main.cpp

#ifndef MAX_USERS
    // default if not defined externally
    #define MAX_USERS 100             // bad - macro  
    constexpr int MAX_USERS_ = 100;   // good - typed, scoped, debuggable
#endif


//// check compiler
// #ifdef _MSC_VER              // MSVC
// #ifdef __GNUC__              // GCC
// #ifdef __clang__             // Clang


//// check cpp version
// #if __cplusplus >= 202002L   // C++20
// #if __cplusplus >= 201703L   // C++17
// #if __cplusplus >= 201402L   // C++14
// #if __cplusplus >= 201103L   // C++11

// better (inside template/function):
// if constexpr (__cplusplus >= 202002L)


//// ifdef vs if defined — identical for single check
// #ifdef  FOO          // simpler
// #if defined(FOO)     // needed for combining conditions
// #if defined(FOO) && defined(BAR)   // ✓ only works with defined()
// #if defined(FOO) || !defined(BAR)  // ✓



}