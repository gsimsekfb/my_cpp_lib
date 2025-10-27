#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <array>
#include <variant>

#include "utils.h"

using std::move;
using std::string;


struct Node {
    int val;
    Node* next;
};

void print_list(Node* list) {
    Node* current = list;
    while(current != nullptr) {
        print(current->val); print(" ");
        current = current->next;
    };
    println("");
}

void advance(Node*& list, size_t len);
Node* find_common_tail(Node* list1, Node* list2);


// --------------- Tests ------------------

TEST_CASE("test-1") {
    println("\n\n---------------");

    Node node_99 = Node { 99, nullptr };
    // 1-2-99
    Node list1 = Node { 1,new Node { 2, &node_99 } };
    // 5-6-7-99
    Node list2 = Node { 5, new Node { 6, new Node { 7, &node_99 } } };

    Node* result = find_common_tail(&list1, &list2);
    print("result: "); print_list(result);

    REQUIRE(result == &node_99);
}

TEST_CASE("test-2") {
    println("\n\n---------------");

    Node node_99 = Node { 99, nullptr };
    Node node_98 = Node { 98, &node_99 };
    // 1-2-98-99
    Node list1 = Node { 1, new Node { 2, &node_98 } };
    // 5-6-7-98-99
    Node list2 = Node { 5, new Node { 6, new Node { 7, &node_98 } } };

    Node* result = find_common_tail(&list1, &list2);
    print("result: "); print_list(result);

    REQUIRE(result == &node_98);
}

TEST_CASE("test-3") {
    println("\n\n---------------");

    Node node_99 = Node { 99, nullptr };
    Node node_98 = Node { 98, &node_99 };
    // 1-98-99
    Node list1 = Node { 1, &node_98 };
    // 5-6-7-98-99
    Node list2 = Node { 5, new Node { 6, new Node { 7, &node_98 } } };

    Node* result = find_common_tail(&list1, &list2);
    print("result: "); print_list(result);

    REQUIRE(result == &node_98);
}

TEST_CASE("test-4") {
    println("\n\n---------------");

    Node node_99 = Node { 99, nullptr };
    Node node_98 = Node { 98, &node_99 };
    // 98-99
    Node list1 = std::move(node_98);
    // 5-6-7-98-99
    Node list2 = Node { 5, new Node { 6, new Node { 7, &list1 } } };

    Node* result = find_common_tail(&list1, &list2);
    print("result: "); print_list(result);

    REQUIRE(result == &list1);
}

TEST_CASE("test-5") {
    println("\n\n---------------");

    Node node_99 = Node { 99, nullptr };
    Node node_98 = Node { 98, &node_99 };
    // 98-99
    Node list1 = std::move(node_98);
    // 5-6-7
    Node list2 = Node { 5, new Node { 6, new Node { 7, nullptr } } };

    Node* result = find_common_tail(&list1, &list2);
    print("result: "); print_list(result);

    REQUIRE(result == nullptr);
}

TEST_CASE("test-6") {
    println("\n\n---------------");

    Node node_99 = Node { 99, nullptr };
    // 99
    Node* list1 = &node_99;
    // 5-6-7-99
    Node list2 = Node { 5, new Node { 6, new Node { 7, list1 } } };

    Node* result = find_common_tail(list1, &list2);
    print("result: "); print_list(result);

    REQUIRE(result == list1);
}

TEST_CASE("test-7") {
    println("\n\n---------------");

    Node node_99 = Node { 99, nullptr };
    // 5-6-7-99
    Node list1 = Node { 5, new Node { 6, new Node { 7, &node_99 } } };
    // 99
    Node* list2 = &node_99;

    Node* result = find_common_tail(&list1, list2);
    print("result: "); print_list(result);

    REQUIRE(result == list2);
}



// --------------- End of Tests ------------------



// 1-2-3-4-5
//   0-3-4-5
Node* find_common_tail(Node* list1, Node* list2) {
    // 1. Find the tails and lens
    print("list1: 0x..."); println(last_n_digit(list1, 4));
    Node* current = list1;
    size_t len1 = 0;
    while(1) {
        print(current->val); print(" ");
        len1 += 1;
        if (current->next == nullptr) break;
        current = current->next;
    };
    println("");
    Node* tail1 = current;
    // print("tail1: 0x..."); println(last_n_digit(tail1, 4));
    print("len1: "); println(len1);

    println("");
    print("list2: 0x..."); println(last_n_digit(list2, 4));
    current = list2;
    size_t len2 = 0;
    while(1) {
        print(current->val); print(" ");
        len2 += 1;
        if (current->next == nullptr) break;
        current = current->next;
    };
    println("");
    Node* tail2 = current;
    // print("tail2: 0x..."); println(last_n_digit(tail2, 4));
    print("len2: "); println(len2);
    
    // 2. Point to same len and parallel search for same node
    (len1 > len2) ? advance(list1, len1-len2) : advance(list2, len2-len1);

    println("");
    println("Advanced to same len:");
    print_list(list1);
    print_list(list2);

    print("list-1: 0x..."); println(last_n_digit(list1, 4));
    print("list-2: 0x..."); println(last_n_digit(list2, 4));
    while(list1 != nullptr && list2 != nullptr) {
        if (list1 == list2) return list1;
        list1 = list1->next;
        list2 = list2->next;  
    }

    return nullptr;
}

void advance(Node*& list, size_t len) {
    print("\n--advance len: "); println(len);
    print("bef: list: 0x..."); println(last_n_digit(list, 4));
    Node* current = list;
    while(current != nullptr && len != 0) {
        --len;
        current = current->next;
        // println("..advanced one step");
    };
    list = current;
    print("aft: list: 0x..."); println(last_n_digit(list, 4));
    // print("list: "); println(list);
}

