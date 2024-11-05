#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "LLRB.h"

void testLLRB() {
    LLRB<int, std::string> tree;
    std::cout << "Starting LLRB tree tests..." << std::endl;

    // Test insertion
    std::cout << "Testing insertion..." << std::endl;
    tree.put(5, "Five");
    tree.put(3, "Three");
    tree.put(7, "Seven");
    tree.put(1, "One");
    tree.put(4, "Four");
    tree.put(6, "Six");
    tree.put(8, "Eight");
    tree.put(10, "Ten");
    std::cout << "Insertion test passed." << std::endl;

    // Test size
    std::cout << "\nTesting size..." << std::endl;
    assert(tree.size() == 8);
    std::cout << "Size test passed." << std::endl;

    // Test retrieval
    std::cout << "\nTesting retrieval..." << std::endl;
    assert(tree.get(5) == "Five");
    assert(tree.get(3) == "Three");
    assert(tree.get(7) == "Seven");
    std::cout << "Retrieval test passed." << std::endl;

    // Test non-existent key retrieval and remove operation
    std::cout << "\nTesting retrieval of non-existent key and remove operation..." << std::endl;
    assert(tree.get(10) == "Ten");
    tree.remove(10);
    try {
        tree.get(10);
        assert(false);
    } catch (const std::out_of_range&) {
        std::cout << "Non-existent key retrieval test passed." << std::endl;
    }

    // Test floor and ceil
    std::cout << "\nTesting floor and ceil functions..." << std::endl;
    assert(tree.Floor(5) == 5);
    assert(tree.Ceil(5) == 5);
    assert(tree.Floor(6) == 6);
    assert(tree.Ceil(6) == 6);
    assert(tree.Floor(2) == 1);
    assert(tree.Ceil(2) == 3);
    std::cout << "Floor and ceil tests passed." << std::endl;

    // Test duplicate insertion
    std::cout << "\nTesting duplicate insertion..." << std::endl;
    tree.put(5, "Five Updated");
    assert(tree.get(5) == "Five Updated");
    std::cout << "Duplicate insertion test passed." << std::endl;

    // Test removal of minimum and maximum
    std::cout << "\nTesting removal of minimum and maximum..." << std::endl;
    assert(tree.min() == 1);
    tree.removeMin();
    assert(tree.min() == 3);
    assert(tree.max() == 8);
    tree.removeMax();
    assert(tree.max() == 7);
    std::cout << "Removal of minimum and maximum test passed." << std::endl;

    // Test size after removals
    std::cout << "\nTesting size after removals..." << std::endl;
    assert(tree.size() == 5);
    std::cout << "Size after removal test passed." << std::endl;

    // Test select
    std::cout << "\nTesting select function..." << std::endl;
    assert(tree.select(0) == 3);
    assert(tree.select(1) == 4);
    assert(tree.select(2) == 5);
    assert(tree.select(3) == 6);
    assert(tree.select(4) == 7);
    std::cout << "Select function test passed." << std::endl;

    // Test edge cases
    std::cout << "\nTesting edge cases for select and remove..." << std::endl;
    try {
        tree.select(5);
        assert(false);
    } catch (const std::out_of_range&) {
        std::cout << "Select out-of-range test passed." << std::endl;
    }

    // Test keys() method
    std::cout << "\nTesting keys() method..." << std::endl;
    std::vector<int> keys = tree.keys();
    std::vector<int> expectedKeys = {3, 4, 5, 6, 7}; // Expected keys in sorted order after removals
    assert(keys == expectedKeys);
    std::cout << "keys() method test passed." << std::endl;

    // Test operator[] for insertion and updating values
    std::cout << "\nTesting operator[]..." << std::endl;
    tree[9] = "Nine"; // Insert new key-value pair
    assert(tree.get(9) == "Nine");

    tree[5] = "Five Again"; // Update existing key
    assert(tree.get(5) == "Five Again");

    std::cout << "operator[] test passed." << std::endl;

    // Test empty tree behavior
    std::cout << "\nTesting empty tree behavior..." << std::endl;
    LLRB<int, std::string> emptyTree;
    try {
        emptyTree.min();
        assert(false);
    } catch (const std::out_of_range&) {
        std::cout << "Empty tree min() test passed." << std::endl;
    }

    try {
        emptyTree.max();
        assert(false);
    } catch (const std::out_of_range&) {
        std::cout << "Empty tree max() test passed." << std::endl;
    }

    try {
        emptyTree.Floor(5);
        assert(false);
    } catch (const std::out_of_range&) {
        std::cout << "Empty tree Floor() test passed." << std::endl;
    }

    try {
        emptyTree.Ceil(5);
        assert(false);
    } catch (const std::out_of_range&) {
        std::cout << "Empty tree Ceil() test passed." << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
    
    /*LLRB<int, std::string> empty;
    empty.put(1, "one");
    empty.put(2, "two");
    //std::cout << empty.size();
    empty.remove(1);
    empty.remove(2);
    std::vector<int> checker = empty.keys();
    for(auto& elem : checker){
        std::cout << elem << "\t";
    }*/
}

int main() {
    testLLRB();
    return 0;
}
