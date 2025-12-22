#include <iostream>
#include <string>

using std::string;

inline size_t hash(const string &key)
{
    const size_t BASE = 31;
    size_t hash = 0;
    for (unsigned char c : key)
    {
        hash = hash * BASE + c;
    }
    return hash;
}

template <typename T>
struct Enty{
    string key;
    T value;
};

template <typename T>
class Map{
    const size_t bucketCount = 201241; // prime number
    Array<Array<Entry<T>>> buckets[bucketCount];

    Map() = default;
    ~Map() = default;

    T* find(string key){
        size_t index = hash(key) % bucketCount;
        auto &bucket = buckets[index];
        
        for(size_t i = 0; i < bucket.size(); i++){
            if(bucket[i].key == key){
                return &bucket[i].value;
            }
        }

        return nullptr;
    }


};


