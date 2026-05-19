#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

    
//// key notes
// - prefer int32_t / int64_t over int / long long for portability
// - prefer size_t for sizes and indices — matches container APIs
// - char signedness is platform dependent — use signed/unsigned char explicitly
// - double is default for floating point — float only when memory critical
// - avoid long — its size varies (32 bit on Windows, 64 bit on Linux)


//// integer — built-in (size is guaranteed minimum, platform may be larger)
// short             ≥ 16 bit   -32,768          → 32,767
// int               ≥ 32 bit   -2,147,483,648   → 2,147,483,647
// long              ≥ 32 bit   platform dependent
// long long         ≥ 64 bit   -9,223,372,036,854,775,808 → 9,223,372,036,854,775,807
// unsigned short    ≥ 16 bit   0 → 65,535
// unsigned int      ≥ 32 bit   0 → 4,294,967,295
// unsigned long long ≥ 64 bit  0 → 18,446,744,073,709,551,615


//// fixed-width integers — <cstdint> — prefer over built-in
// int8_t            exactly  8 bit signed
// int16_t           exactly 16 bit signed
// int32_t           exactly 32 bit signed
// int64_t           exactly 64 bit signed
// uint8_t           exactly  8 bit unsigned
// uint16_t          exactly 16 bit unsigned
// uint32_t          exactly 32 bit unsigned
// uint64_t          exactly 64 bit unsigned


//// floating point
// float             32 bit   ~7  decimal digits precision   suffix: F
// double            64 bit   ~15 decimal digits precision
// long double       ≥ 64 bit ~18 decimal digits precision   suffix: L


//// character
// char              8 bit    may be signed or unsigned — platform dependent
// signed char       8 bit    -128 → 127
// unsigned char     8 bit    0 → 255
// wchar_t           platform dependent (16 or 32 bit)
// char8_t           8 bit    UTF-8  (C++20)
// char16_t          16 bit   UTF-16 (C++11)
// char32_t          32 bit   UTF-32 (C++11)


//// boolean
// bool              1 byte   true / false


//// void
// void              no size  used for functions returning nothing, void* ptrs


//// size / pointer types — <cstddef>
// size_t            unsigned — result of sizeof, container sizes, indices
// ptrdiff_t         signed   — difference between two pointers
// nullptr_t         type of nullptr (C++11)
// intptr_t          signed integer large enough to hold a pointer
// uintptr_t         unsigned integer large enough to hold a pointer


//// literal suffixes
// 42                int
// 42U               unsigned int
// 42L               long
// 42UL              unsigned long
// 42LL              long long
// 42ULL             unsigned long long
// 3.14F             float
// 3.14              double
// 3.14L             long double
// 'a'               char
// u8"hi"            char8_t  string (C++20)
// u"hi"             char16_t string
// U"hi"             char32_t string
// L"hi"             wchar_t  string

}
