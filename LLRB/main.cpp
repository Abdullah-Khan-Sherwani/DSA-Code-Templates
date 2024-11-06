#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "LLRBDeluxe.h"

void testLLRBDeluxe()
{
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
    try
    {
        tree.get(10);
        assert(false);
    }
    catch (const std::out_of_range &)
    {
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
    try
    {
        tree.select(5);
        assert(false);
    }
    catch (const std::out_of_range &)
    {
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
    try
    {
        emptyTree.min();
        assert(false);
    }
    catch (const std::out_of_range &)
    {
        std::cout << "Empty tree min() test passed." << std::endl;
    }

    try
    {
        emptyTree.max();
        assert(false);
    }
    catch (const std::out_of_range &)
    {
        std::cout << "Empty tree max() test passed." << std::endl;
    }

    try
    {
        emptyTree.Floor(5);
        assert(false);
    }
    catch (const std::out_of_range &)
    {
        std::cout << "Empty tree Floor() test passed." << std::endl;
    }

    try
    {
        emptyTree.Ceil(5);
        assert(false);
    }
    catch (const std::out_of_range &)
    {
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

template <typename Key, typename Value>
void testLLRB()
{
    LLRB<Key, Value> tree;

    // Test 1: Insert and Get
    tree.put(1, 10);
    tree.put(2, 20);
    tree.put(3, 30);
    tree.put(4, 40);

    assert(tree.get(1) == 10 && "Test 1 failed: Expected value for key 1 is 10");
    assert(tree.get(2) == 20 && "Test 1 failed: Expected value for key 2 is 20");
    assert(tree.get(3) == 30 && "Test 1 failed: Expected value for key 3 is 30");
    assert(tree.get(4) == 40 && "Test 1 failed: Expected value for key 4 is 40");

    std::cout << "Test 1 passed: Insert and Get" << std::endl;

    // Test 2: Update value for existing key
    tree.put(2, 25); // Update value of key 2 to 25
    assert(tree.get(2) == 25 && "Test 2 failed: Expected updated value for key 2 is 25");
    std::cout << "Test 2 passed: Update value for existing key" << std::endl;

    // Test 3: Test size function
    assert(tree.size() == 4 && "Test 3 failed: Expected tree size is 4");
    /*tree.remove(2); // Remove key 2
    assert(tree.size() == 3 && "Test 3 failed: Expected tree size after removing key 2 is 3");*/
    std::cout << "Test 3 passed: Size function" << std::endl;

    // Test 4: Test floor and ceil
    tree.put(5, 50);
    assert(tree.Floor(5) == 5 && "Test 4 failed: Expected floor of 5 is 5");
    assert(tree.Floor(6) == 5 && "Test 4 failed: Expected floor of 6 is 5");
    assert(tree.Ceil(5) == 5 && "Test 4 failed: Expected ceil of 5 is 5");
    assert(tree.Ceil(4) == 4 && "Test 4 failed: Expected ceil of 4 is 4");
    std::cout << "Test 4 passed: Floor and Ceil" << std::endl;

    // Test 5: Test min and max
    assert(tree.min() == 1 && "Test 5 failed: Expected min key is 1");
    assert(tree.max() == 5 && "Test 5 failed: Expected max key is 5");
    std::cout << "Test 5 passed: Min and Max" << std::endl;

    // Test 6: Test rank function
    assert(tree.rank(1) == 0 && "Test 6 failed: Expected rank of key 1 is 0");
    assert(tree.rank(3) == 2 && "Test 6 failed: Expected rank of key 3 is 2");
    assert(tree.rank(5) == 4 && "Test 6 failed: Expected rank of key 5 is 4");
    std::cout << "Test 6 passed: Rank function" << std::endl;

    // Test 7: Test select function
    assert(tree.select(0) == 1 && "Test 7 failed: Expected key at rank 0 is 1");
    assert(tree.select(1) == 2 && "Test 7 failed: Expected key at rank 1 is 2");
    assert(tree.select(2) == 3 && "Test 7 failed: Expected key at rank 2 is 3");
    assert(tree.select(3) == 4 && "Test 7 failed: Expected key at rank 3 is 5");
    std::cout << "Test 7 passed: Select function" << std::endl;

    // Test 8: Remove and check tree consistency
    /*tree.remove(3);
    assert(tree.size() == 3 && "Test 8 failed: Expected tree size after removing key 3 is 3");
    assert(tree.get(4) == 40 && "Test 8 failed: Expected value for key 4 is 40");
    try
    {
        tree.get(3); // Should throw an exception
        assert(false && "Test 8 failed: Expected exception when getting removed key 3");
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Test 8 passed: Remove key and ensure consistency" << std::endl;
    }*/

    // Test 9: Remove min and max
    /*tree.removeMin();
    assert(tree.min() == 3 && "Test 9 failed: Expected new min key after removing min is 3");

    tree.removeMax();
    assert(tree.max() == 4 && "Test 9 failed: Expected new max key after removing max is 4");

    std::cout << "Test 9 passed: Remove min and max" << std::endl;*/

    // Test 10: Test empty tree behavior
    LLRB<int, int> emptyTree;
    try
    {
        emptyTree.min(); // Should throw an exception
        assert(false && "Test 10 failed: Expected exception when calling min on empty tree");
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Test 10 passed: Exception on empty tree min()" << std::endl;
    }

    try
    {
        emptyTree.max(); // Should throw an exception
        assert(false && "Test 10 failed: Expected exception when calling max on empty tree");
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Test 10 passed: Exception on empty tree max()" << std::endl;
    }

    try
    {
        emptyTree.get(1); // Should throw an exception
        assert(false && "Test 10 failed: Expected exception when calling get on empty tree");
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Test 10 passed: Exception on empty tree get()" << std::endl;
    }

    // Test 11: Test large insertions
    for (int i = 0; i < 1000; ++i)
    {
        tree.put(i, i * 10);
    }
    assert(tree.size() == 1000 && "Test 11 failed: Expected tree size after inserting 1000 elements");
    assert(tree.get(999) == 9990 && "Test 11 failed: Expected value for key 999 is 9990");
    std::cout << "Test 11 passed: Large insertions" << std::endl;

    // Test 12: Test edge case for rank
    tree.put(1001, 10010);
    assert(tree.rank(1001) == 1000 && "Test 12 failed: Expected rank for key 1001 is 1001");
    std::cout << "Test 12 passed: Edge case for rank" << std::endl;
}

int main()
{
    // testLLRBDeluxe();
    try
    {
        testLLRB<int, int>();
        std::cout << "All tests passed!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Test failed: " << e.what() << std::endl;
    }
    return 0;
}
