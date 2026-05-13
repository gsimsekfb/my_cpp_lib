#include <thread>
#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;


//// thread_local
//// - gives each thread its own independent copy of the variable.
////
//// Key notes: 
//// - lifetime — tied to thread, not program
//// - mental model: what static is to programs, thread_local is to threads  

thread_local int counter = 10;

void work(int thread_id) {
    thread_id == 1 ? ++counter : --counter;
    std::cout << "Thread " << thread_id << ": counter = " << counter << "\n";
}

TEST_CASE("thr-loc-1") {
    std::thread t1 {work, 1};
    std::thread t2 {work, -1};
    t1.join();
    t2.join();

    std::cout << "Thread main: counter = " << counter << "\n";

    REQUIRE(counter == 10);
}
    // Thread -1: counter = 9
    // Thread 1: counter = 11
    // Thread main: counter = 10   