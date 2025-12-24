#include <iostream>
#include <string>
#include "Array.hpp"

using std::string;

inline std::size_t hash(const string &key) {
    const std::size_t BASE = 31;
    std::size_t h = 0;
    for (unsigned char c : key) {
        h = h * BASE + c;
    }
    return h;
}

template <typename T>
class Set {
public:
    static constexpr std::size_t bucketCount = 201241;
    Array<T>* buckets;

    Set() {
        buckets = new Array<T>[bucketCount];
    }

    ~Set() {
        delete[] buckets;
    }

    void insert(const T& key) {
        if (contains(key)) return; 

        std::size_t index = getIndex(key);
        buckets[index].append(key);
    }

    bool contains(const T& key) const {
        std::size_t index = getIndex(key);
        Array<T>& bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i] == key) {
                return true;
            }
        }
        return false;
    }

    bool remove(const T& key) {
        std::size_t index = getIndex(key);
        Array<T>& bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i] == key) {
                bucket.removeAt(i);
                return true;
            }
        }
        return false;
    }

private:
    std::size_t getIndex(const string& key) const {
        return hash(key) % bucketCount;
    }
};