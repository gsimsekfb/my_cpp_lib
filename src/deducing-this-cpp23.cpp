#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// deducing this lets you write the object's type and value category 
// explicitly as a parameter — eliminating const/ref overload duplication.

//
// Key notes:

//// C++23 — one function, self deduces all combinations
struct Buffer {
    std::string data;

    auto&& get(this auto&& self) {
        return std::forward_like<decltype(self)>(self.data);  // ✓
    }
};

// instead of
struct Buffer_ {
    std::string data;

    std::string& get() &             { return data; }  // non-const lvalue
    const std::string& get() const&  { return data; }  // const lvalue
    std::string&& get() &&           { return std::move(data); } // rvalue
    const std::string&& get() const&& { return std::move(data); } // const rvalue
};


}