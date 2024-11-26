#include <iostream>
#include <string>
#include "LinearProbingHashST.hpp" 

int main() {
    // Create an instance of LinearProbingHashST with default capacity
    LinearProbingHashST<std::string, int> hashTable;

    // Insert key-value pairs into the hash table
    std::cout << "Inserting key-value pairs...\n";
    hashTable.put("Alice", 25);
    hashTable.put("Bob", 30);
    hashTable.put("Charlie", 35);

    // Retrieve values for inserted keys
    std::cout << "\nRetrieving values:\n";
    std::cout << "Alice: " << hashTable.get("Alice").value_or(-1) << "\n";
    std::cout << "Bob: " << hashTable.get("Bob").value_or(-1) << "\n";
    std::cout << "Charlie: " << hashTable.get("Charlie").value_or(-1) << "\n";

    // Test updating a value
    std::cout << "\nUpdating Bob's value to 50...\n";
    hashTable.put("Bob", 50);
    std::cout << "Bob: " << hashTable.get("Bob").value_or(-1) << "\n";

    // Test removing a key
    std::cout << "\nRemoving Alice...\n";
    hashTable.remove("Alice");
    std::cout << "Alice after removal: " << hashTable.get("Alice").value_or(-1) << "\n";

    // Test key existence
    std::cout << "\nChecking key existence:\n";
    std::cout << "Contains Bob? " << (hashTable.contains("Bob") ? "Yes" : "No") << "\n";
    std::cout << "Contains Alice? " << (hashTable.contains("Alice") ? "Yes" : "No") << "\n";

    // Insert more key-value pairs to trigger resizing
    std::cout << "\nInserting more key-value pairs to test resizing...\n";
    for (int i = 1; i <= 20; ++i) {
        hashTable.put("Key" + std::to_string(i), i * 10);
    }
    std::cout << "Hash table size after resizing: " << hashTable.size() << "\n";

    // Retrieve a few of the inserted keys
    std::cout << "\nRetrieving a few values:\n";
    std::cout << "Key5: " << hashTable.get("Key5").value_or(-1) << "\n";
    std::cout << "Key15: " << hashTable.get("Key15").value_or(-1) << "\n";

    // Test if the hash table is empty
    std::cout << "\nIs the hash table empty? " << (hashTable.isEmpty() ? "Yes" : "No") << "\n";

    // Test size of the hash table
    std::cout << "Number of entries in the hash table: " << hashTable.size() << "\n";

    return 0;
}
