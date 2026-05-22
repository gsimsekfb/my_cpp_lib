#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()

#include "utils.h"

using namespace std;

namespace {

// all cast types     when to use which
// ---------------------------------------------------------------------------
// static_cast        compile-time, no runtime check  — numeric, upcast, void*
// dynamic_cast       runtime check, safe downcast    — polymorphic types
// const_cast         add/remove const                — legacy C API interop
// reinterpret_cast   raw bit reinterpretation        — low level, dangerous

//// all casts comparison
// static_cast       — compile-time, related types, numeric
// dynamic_cast      — runtime, safe downcast, polymorphic
// const_cast        — add/remove const only
// reinterpret_cast  — raw bits, anything to anything, dangerous

}