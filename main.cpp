#include <algorithm>
#include <iostream>
#include <vector>

#include "utils.h"

using namespace std;

// // cpp20
// void erase_negatives_2020(std::vector<int>& vec) {
//     std::erase_if(vec, [](int e) { return e < 0; } );
// }

// cpp11-17
void erase_negatives_2011(std::vector<int>& vec) {
    for (auto it = vec.begin(); it != vec.end();) {
        // dbg(*it);
        if (*it % 2 == 0) {
            it = vec.erase(it); // ! iterator invalidation risk, vec may resize
        } else {
            ++it;
        }
    }
}

int main() {
    std::cout << "\n================== main start \n" << std::endl;

    print_cpp_version();

    vector<int> v { -1, 2, -3, 4, -5};
    print_vec(v);


    std::cout << "\n================== main end" << std::endl;
    return 0;
}