# pragma once

#include <vector>
#include <optional>
#include <functional>

template <typename Key, typename Value>
class LinearProbingHashST {
private:
    int M; 
    int N; 
    std::vector<std::optional<Key>> keys; 
    std::vector<std::optional<Value>> vals; 

    int hash(const Key& key) const {
        return std::hash<Key>{}(key) % M;
    }

    void resize(int capacity) {
        LinearProbingHashST<Key, Value> temp(capacity);
        for (int i = 0; i < M; i++) {
            if (keys[i].has_value()) {
                temp.put(keys[i].value(), vals[i].value());
            }
        }
        *this = std::move(temp);
    }

public:
    LinearProbingHashST(int capacity = 30001) : M(capacity), N(0), keys(M), vals(M) {}

    std::optional<Value> get(const Key& key) {
        for (int i = hash(key); keys[i].has_value(); i = (i + 1) % M) {
            if (keys[i].value() == key) {
                return vals[i];
            }
        }
        return std::nullopt; 
    }

    void put(const Key& key, const Value& val) {
        if (N >= M / 2) resize(2 * M); // Resize if load factor >= 0.5

        int i;
        for (i = hash(key); keys[i].has_value(); i = (i + 1) % M) {
            if (keys[i].value() == key) {
                vals[i] = val; 
                return;
            }
        }
        keys[i] = key;
        vals[i] = val;
        N++; 
    }

    void remove(const Key& key) {
        if (!get(key).has_value()) return; 

        int i = hash(key);
        while (keys[i].has_value()) {
            if (keys[i].value() == key) break;
            i = (i + 1) % M;
        }

        keys[i].reset();
        vals[i].reset();
        N--;

        i = (i + 1) % M;
        while (keys[i].has_value()) {
            Key tempKey = keys[i].value();
            Value tempVal = vals[i].value();
            keys[i].reset();
            vals[i].reset();
            N--;
            put(tempKey, tempVal); 
            i = (i + 1) % M;
        }

        if (N > 0 && N <= M / 8) resize(M / 2); 
    }

    bool contains(const Key& key) {
        return get(key).has_value();
    }

    bool isEmpty() const {
        return N == 0;
    }

    int size() const {
        return N;
    }
};
