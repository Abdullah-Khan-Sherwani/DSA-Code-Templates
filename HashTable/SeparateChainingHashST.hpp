#pragma

#include <list>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

template<typename Key, typename Value>
class SeparateChainingHashST{
    int size;
    std::vector<std::list<std::pair<Key, Value>>> hashtable;

    int hash(const Key &key) const {
        // Step 1: Generate Hash Value using std::hash
        std::hash<Key> hash_func;
        size_t hashValue = hash_func(key);
        
        // Step 2: Compute Index
        return hashValue % size;
    }

    public:
    SeparateChainingHashST(int size) : size(size), hashtable(size) {}

    void insert(const Key &key, Value val){
        int location = hash(key);

        for(const auto& p : hashtable[location]){
            if(p.first == key && p.second == val){
                return;
            }
        }

        hashtable[location].emplace_back(key, val);
    }

    bool contains(const Key &key) const
    {
        int location = hash(key);

        for (const auto &pair : hashtable[location])
        {
            if (key == pair.first)
            {
                return true; 
            }
        }

        return false; 
    }

    void remove(Key key){
        int index = hash(key);
        auto& lst = hashtable[index];

        for (auto it = lst.begin(); it != lst.end(); ++it) { 
            if (it->first == key) { 
                lst.erase(it);    
                return;
            }
        }
        throw std::out_of_range("Key not found");
    }
};