#include <iostream>
#include <string>
#include <stdexcept>
#include "SeparateChainingHashST.hpp"  

int main() {
    // Create a SeparateChainingHashST instance with key type as string and value type as int
    SeparateChainingHashST<std::string, int> hashTable(10);  // size 10 for simplicity

    // Test insertion and contains
    hashTable.insert("apple", 5);
    hashTable.insert("banana", 3);
    hashTable.insert("cherry", 7);

    std::cout << "Inserting key-value pairs: apple->5, banana->3, cherry->7" << std::endl;

    // Check if the table contains the keys
    if (hashTable.contains("apple")) {
        std::cout << "The key 'apple' is in the table." << std::endl;
    } else {
        std::cout << "The key 'apple' is not in the table." << std::endl;
    }

    if (hashTable.contains("banana")) {
        std::cout << "The key 'banana' is in the table." << std::endl;
    } else {
        std::cout << "The key 'banana' is not in the table." << std::endl;
    }

    if (hashTable.contains("grape")) {
        std::cout << "The key 'grape' is in the table." << std::endl;
    } else {
        std::cout << "The key 'grape' is not in the table." << std::endl;
    }

    // Test removing a key
    try {
        hashTable.remove("banana");
        std::cout << "The key 'banana' has been removed." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    // Test if 'banana' was removed
    if (hashTable.contains("banana")) {
        std::cout << "The key 'banana' is still in the table." << std::endl;
    } else {
        std::cout << "The key 'banana' was successfully removed." << std::endl;
    }

    // Test removing a key that doesn't exist
    try {
        hashTable.remove("grape");  // This key doesn't exist
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;  // Expected
    }

    // Test inserting duplicate key-value pair
    hashTable.insert("apple", 5);  // This shouldn't insert a duplicate
    std::cout << "Attempting to insert duplicate: apple->5" << std::endl;
    if (hashTable.contains("apple")) {
        std::cout << "The key 'apple' is still in the table." << std::endl;
    }

    return 0;
}
