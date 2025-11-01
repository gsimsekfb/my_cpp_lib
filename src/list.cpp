#include <utility>
#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <cstdlib>

#include "utils.h"


// Last: 11.25

// Task:
// Given two linked lists, determine if they share a common tail 
// (i.e., they converge at some node and share all subsequent nodes). 
// If they do, return the node where they merge. If not, return null
// Report time and space complexity




// -----------------------------------------------------------------------



struct Node {
    int val;
    Node* next;
};

void print_list(const Node* list) {
    while(list != nullptr) {
        print(list->val); print(" ");
        list = list->next;
    };
    println("");
}

void advance(const Node*& list, size_t len) {
    // print("bef: list: 0x..."); println(last_n_digit(list, 4));
    while(list != nullptr && len != 0) {
        --len;
        list = list->next;
    };
    // print("aft: list: 0x..."); println(last_n_digit(list, 4));
}

std::pair<size_t, const Node*> find_len_and_last_node(const Node* list) {
    size_t len = 0;
    while(list != nullptr) {
        ++len;
        if (list->next == nullptr) break;
        list = list->next;
    };
    return {len, list};
}

const Node* find_common_tail(const Node* list1, const Node* list2) {
    print("list1: "); print_list(list1);
    print("list2: "); print_list(list2);

    // Step-1. Find lens and last_nodes
    auto [len1, last_node_1] = find_len_and_last_node(list1);
    auto [len2, last_node_2] = find_len_and_last_node(list2);
 
    if (last_node_1 != last_node_2) {
        println("-- early return, last_node_s are different ..");
        return nullptr;
    }
    
    // Step-2. Advance to same len
    if(len1 > len2) advance(list1, len1-len2);
    else            advance(list2, len2-len1);

    // Step-3. Parallel search for same node
    while(list1 != nullptr) {
        if (list1 == list2) return list1;
        list1 = list1->next;
        list2 = list2->next;  
    }

    return nullptr;
}





// --------------- Tests ------------------

TEST_CASE("test-1") {
    println("\n\n---------------");

    Node node_99 = Node { 99, nullptr };
    // 1-2-99
    Node list1 = Node { 1,new Node { 2, &node_99 } };
    // 5-6-7-99
    Node list2 = Node { 5, new Node { 6, new Node { 7, &node_99 } } };

    const Node* result = find_common_tail(&list1, &list2);
    print("result: "); print_list(result);

    print_list(&list1);
    print_list(&list2);

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

    const Node* result = find_common_tail(&list1, &list2);
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

    const Node* result = find_common_tail(&list1, &list2);
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

    const Node* result = find_common_tail(&list1, &list2);
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

    const Node* result = find_common_tail(&list1, &list2);
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

    const Node* result = find_common_tail(list1, &list2);
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

    const Node* result = find_common_tail(&list1, list2);
    print("result: "); print_list(result);

    REQUIRE(result == list2);
}



// --------------- End of Tests ------------------

