#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// before C++17 — verbose
namespace Foo {
    namespace Bar {
        namespace Baz {
            void fn() {}
        }
    }
}

// C++17 — inline nesting
namespace Foo::Bar::Baz {
    void fn_() {}
}

// C++20 — "inline" namespaces in nested form
namespace Foo::Bar::inline Bazz {
    void fn__() {}  // Baz members accessible via Foo::Bar:: directly
}

TEST_CASE("nam-nes-1") {

    // usage
    Foo::Bar::Bazz::fn__();  // full path
    Foo::Bar::fn__();        // shortcut path due to inline Bazz

    using namespace Foo::Bar::Bazz;
    // or
    using namespace Foo::Bar;
    fn__();                 // direct ✓

}