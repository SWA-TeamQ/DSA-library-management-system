#include <iostream>
#include <string>
#include <Array.hpp>
#include <stdexcept>

using std::string;

inline std::size_t hash(const string &key)
{
    const std::size_t BASE = 31;
    std::size_t h = 0;
    for (unsigned char c : key)
    {
        h = h * BASE + c;
    }
    return h;
}

template <typename T>
struct Entry{
    string key;
    T value;
};

template <typename T>
class Map{
public:
    static constexpr std::size_t bucketCount = 201241; // prime number
    Array<Entry<T>> buckets[bucketCount];

    Map() = default;
    ~Map() = default;

    void insert(const string& key, const T& value) {
        std::size_t index = getIndex(key);
        Array<Entry<T>>& bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].key == key) {
                bucket[i].value = value;
                return;
            }
        }
        bucket.append({key, value});
    }

    T* find(const string& key){
        std::size_t index = getIndex(key);
        Array<Entry<T>>& bucket = buckets[index];
        
        for(std::size_t i = 0; i < bucket.size(); i++){
            if(bucket[i].key == key){
                return &bucket[i].value;
            }
        }

        return nullptr;
    }

    bool remove(const string& key) {
        std::size_t index = getIndex(key);
        Array<Entry<T>>& bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++) {
            if (bucket[i].key == key) {
                bucket.removeAt(i);
                return true;
            }
        }
        return false;
    }

    T& operator[](const string& key) {
        T* existing = find(key);
        if (existing) return *existing;

        insert(key, T());
        return *find(key);
    }

    T& at(const string& key) {
        T* result = find(key);

        if (result == nullptr) {
        throw std::out_of_range("Map::at() : key not found in map");
        }

        return *result;
    }

    //I added this function because you have a read-only function in the Array.hpp

    const T& at(const string& key) const {
        std::size_t index = getIndex(key);
        const Array<Entry<T>>& bucket = buckets[index];
    
        for(std::size_t i = 0; i < bucket.size(); i++){
            if (bucket[i].key == key){
                return bucket[i].value;
            }
        }
        throw std::out_of_range("Map::at() : key not found in const map");
    }

    void clear(){
        for(int i=0;i<bucketCount;i++){
            Array<Entry<T>>& bucket = buckets[i];
            bucket.clear();
        }
    }

private:
    std::size_t getIndex(const string& key) const {
        return hash(key) % bucketCount;
    }
};