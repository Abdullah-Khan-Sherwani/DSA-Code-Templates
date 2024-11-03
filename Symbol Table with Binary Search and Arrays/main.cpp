#include <iostream>
#include <vector>
#include <exception>
using namespace std;

template<typename Key, typename Value>
class ST {
    vector<Key> keys;
    vector<Value> values;

    // Uses Binary Search to find the placement of given key
    //Will be used for insertion etc
    int rank(Key key) {
        int lo = 0, hi = keys.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (keys[mid] < key) {
                lo = mid + 1;
            }
            else if (keys[mid] > key) {
                hi = mid - 1;
            }
            else {
                return mid;
            }
        }
        return lo;
    }

public:
    ST(int n) : keys(n), values(n) {}
    ST() {}

    bool empty() {
        return keys.empty();
    }

    void put(Key key, Value value) {
        int place = rank(key);

        if (place < keys.size() && keys[place] == key) {
            values[place] = value;
        }
        else {
            keys.insert(keys.begin() + place, key);
            values.insert(values.begin() + place, value);
        }
    }

    Value get(Key key) {
        if (empty()) throw std::out_of_range("Symbol table is empty");
        int place = rank(key);

        if (place < keys.size() && keys[place] == key) {
            return values[place];
        }
        else {
            throw std::out_of_range("Key not found");
        }
    }

    bool contains(Key key) {
        int place = rank(key);
        return place < keys.size() && keys[place] == key;
    }

    size_t size() {
        return keys.size();
    }

    vector<Key> allKeys() {
        return keys;
    }

    Value& operator[](Key key) {
        int place = rank(key);

        if (place < keys.size() && keys[place] == key) {
            return values[place];
        }
        else {
            keys.insert(keys.begin() + place, key);
            values.insert(values.begin() + place, Value{});
            return values[place];
        }
    }
};

//GPT made
// Client program to test ST class
int main() {
    ST<int, string> st;

    // Testing put method
    st.put(5, "five");
    st.put(3, "three");
    st.put(9, "nine");

    // Testing get method
    try {
        cout << "Value for key 5: " << st.get(5) << endl;
        cout << "Value for key 3: " << st.get(3) << endl;
        cout << "Value for key 9: " << st.get(9) << endl;
        cout << "Value for key 10: "<< st.get(10) << endl;
    } catch (const std::out_of_range& e) {
        cout << e.what() << endl;
    }

    // Testing operator[]
    cout << "\nAccessing key 1 with operator[] (should create default): " << st[1] << endl;
    st[1] = "one"; // Modify the value for the new key
    cout << "Updated value for key 1: " << st[1] << endl;

    // Testing contains
    cout << "\nContains key 3? " << (st.contains(3) ? "Yes" : "No") << endl;
    cout << "Contains key 7? " << (st.contains(7) ? "Yes" : "No") << endl;

    // Displaying all keys
    cout << "\nAll keys in the symbol table: ";
    for (const auto& key : st.allKeys()) {
        cout << key << " ";
    }
    cout << endl;

    // Testing size
    cout << "\nSize of symbol table: " << st.size() << endl;

    return 0;
}
