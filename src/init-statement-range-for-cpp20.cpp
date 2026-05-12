#include <mutex>
#include <thread>
#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"


#include "utils.h"

using namespace std;

TEST_CASE("isr-1-simplest-example") {
    vector vec = {'a', 'b', 'c'};
    for(int i = 0; auto const& e : vec) {
        print(++i); println(e);
    }
    // i is no longer in scope here

    // instead of
    int i = 0;    
    for(auto const& e : vec) {
        print(++i); println(e);
    }
    // !! i leaks here

    REQUIRE(i == 3);
}

TEST_CASE("isr-2") {
    vector vec = {1, 2, 3};

    std::mutex mtx;
    auto foo = [&] () {
        for(std::lock_guard lock(mtx); auto& e : vec)
            e *= 10;
    };
    // ✓ mutex unlocked here automatically

    std::thread t1 {foo};
    std::thread t2 {foo};
    t1.join();
    t2.join();

    print_vec(vec);

    // REQUIRE(i == 3);
}