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
struct Entry
{
    string key;
    T value;
};

template <typename T>
class unordered_map
{
public:
    static constexpr std::size_t bucketCount = 201241; // prime number
    Array<Entry<T>> *buckets;

    unordered_map()
    {
        buckets = new Array<Entry<T>>[bucketCount];
    }
    ~unordered_map()
    {
        delete[] buckets;
    }
    class Iterator
    {
    private:
        const unordered_map *mapPtr;
        size_t bIdx; // current_bucket_index
        size_t eIdx; // current_element_index_inside_bucket
        // helper method
        void advance()
        {
            eIdx++;
            while (bIdx < mapPtr->bucketCount && eIdx >= mapPtr->buckets[bIdx].size())
            {
                bIdx++;
                eIdx = 0;
            }
        }

    public:
        Iterator(const unordered_map *m, , size_t b, size_t e) : mapPtr(m), bIdx(b), eIdx(e)
        {
            if (bIdx < mapPtr->bucketCount && (mapPtr->buckets[bIdx].empty()))
            {
                advance();

                if (bIdx >= mapPtr->bucketCount)
                    eIdx = 0;
            }
        }

        bool operator!=(const Iterator &other) const
        {
            return bIdx != other.bIdx || eIdx != other.eIdx;
        }

        Iterator &operator++()
        {
            advance();
            return *this;
        }

        const Entry<T> &operator*() const
        {
            return mapPtr->buckets[bIdx][eIdx];
        }

        const Entry<T> *operator->() const
        {
            return &(mapPtr->buckets[bIdx][eIdx])
        }
    };

    Iterator begin() const
    {
        return Iterator(this, 0, 0);
    }

    Iterator end() const
    {
        return Iterator(this, bucketCount, 0);
    }

    void insert(const string &key, const T &value)
    {
        std::size_t index = getIndex(key);
        Array<Entry<T>> &bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++)
        {
            if (bucket[i].key == key)
            {
                bucket[i].value = value;
                return;
            }
        }
        bucket.append({key, value});
    }

    T *find(const string &key)
    {
        std::size_t index = getIndex(key);
        Array<Entry<T>> &bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++)
        {
            if (bucket[i].key == key)
            {
                return &bucket[i].value;
            }
        }

        return nullptr;
    }

    bool remove(const string &key)
    {
        std::size_t index = getIndex(key);
        Array<Entry<T>> &bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++)
        {
            if (bucket[i].key == key)
            {
                bucket.removeAt(i);
                return true;
            }
        }
        return false;
    }

    Array<Entry<T>> getAllEntries() const
    {
        Array<Entry<T>> all;
        for (std::size_t i = 0; i < bucketCount; i++)
        {
            for (std::size_t j = 0; j < buckets[i].size(); j++)
            {
                all.append(buckets[i][j]);
            }
        }
        return all;
    }

    T &operator[](const string &key)
    {
        T *existing = find(key);
        if (existing)
            return *existing;

        insert(key, T());
        return *find(key);
    }

    T &at(const string &key)
    {
        T *result = find(key);

        if (result == nullptr)
        {
            throw std::out_of_range("Map::at() : key not found in map");
        }

        return *result;
    }

    // I added this function because you have a read-only function in the Array.hpp

    const T &at(const string &key) const
    {
        std::size_t index = getIndex(key);
        const Array<Entry<T>> &bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++)
        {
            if (bucket[i].key == key)
            {
                return bucket[i].value;
            }
        }
        throw std::out_of_range("Map::at() : key not found in const map");
    }

    bool isEmpty() const
    {
        for (int i = 0; i < bucketCount; i++)
        {
            Array<Entry<T>> &bucket = buckets[i];
            if (!bucket.empty())
            {
                return false;
            }
        }
        return true;
    }

    void clear()
    {
        for (int i = 0; i < bucketCount; i++)
        {
            Array<Entry<T>> &bucket = buckets[i];
            bucket.clear();
        }
    }

private:
    std::size_t getIndex(const string &key) const
    {
        return hash(key) % bucketCount;
    }
};