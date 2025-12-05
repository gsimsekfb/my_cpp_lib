#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "src\utils.h"

using namespace std;


int main() {
    std::cout << "\n================== main start \n";
    print_cpp_version();


    int sum = 0;
    for (int i = 0; i < 4; i++) {
        // println(i);
        sum += i;
    };

    auto res = sum;
    dbg( res );

    // pinned
    // --------------------
    // vector<int> v { 1, 2, 3 };
    // dbg(&vec);
    // print_vec(v);
    // ---------------------
    std::cout << "\n================== main end" << std::endl;
    return 0;
}