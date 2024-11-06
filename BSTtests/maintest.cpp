#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "BSTClass.h"

int main() {
    // Create a BST and add some initial values
    BST<int, std::string> bst;
    bst.put(10, "Root");
    bst.put(5, "Left child");
    bst.put(20, "Right child");
    bst.put(15, "Right-Left child");
    bst.put(30, "Right-Right child");
    
    // Test 1: Removing a non-existent key (should not throw an error, just handle gracefully)
    try {
        bst.remove(100);
        std::cout << "Pass: Removing non-existent key handled correctly.\n";
    } catch (const std::exception &e) {
        std::cerr << "Fail: Exception when removing non-existent key.\n";
    }

    // Test 2: Remove a leaf node
    bst.remove(15);  // 15 is a leaf node in this tree
    assert(bst.size() == 4);  // Size should decrease by 1
    auto keys = bst.keys();
    assert(std::find(keys.begin(), keys.end(), 15) == keys.end());
    std::cout << "Pass: Removing a leaf node.\n";

    // Test 3: Remove a node with one child
    bst.remove(20);  // 20 has only one child (node 30)
    assert(bst.size() == 3);
    keys = bst.keys();
    assert(std::find(keys.begin(), keys.end(), 20) == keys.end());
    std::cout << "Pass: Removing a node with one child.\n";

    // Test 4: Remove the root node (10) when it has two children
    bst.remove(10);
    assert(bst.size() == 2);
    keys = bst.keys();
    assert(std::find(keys.begin(), keys.end(), 10) == keys.end());
    std::cout << "Pass: Removing the root node with two children.\n";

    // Test 5: Remove remaining nodes until tree is empty
    bst.remove(5);
    bst.remove(30);  // Last node
    assert(bst.size() == 0);
    std::cout << "Pass: Removing all nodes until empty.\n";

    // Test 6: Repeatedly remove min and max
    bst.put(50, "Root");
    bst.put(40, "Left");
    bst.put(60, "Right");

    bst.removeMin();
    assert(bst.size() == 2);
    assert(bst.min() == 50);

    bst.removeMax();
    assert(bst.size() == 1);
    assert(bst.max() == 50);
    std::cout << "Pass: Removing min and max nodes.\n";

    std::cout << "All tests passed successfully.\n";
    return 0;
}
