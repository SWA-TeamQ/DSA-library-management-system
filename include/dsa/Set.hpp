#include <iostream>
#include <string>
#include "Array.hpp"

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
class unordered_set
{
public:
    static constexpr std::size_t bucketCount = 201241;
    Array<T> *buckets;

    unordered_set()
    {
        buckets = new Array<T>[bucketCount];
    }

    ~unordered_set()
    {
        delete[] buckets;
    }
    class Iterator
    {
    private:
        const unordered_set *setPtr;
        size_t bIdx;
        size_t eIdx;

        void advance()
        {
            eIdx++;
            while (bIdx < setPtr->bucketCount && eIdx >= setPtr->buckets[bIdx].size())
            {
                bIdx++;
                eIdx = 0;
            }
        }

    public:
        Iterator(const unordered_set *s, size_t b, size_t e)
            : setPtr(s), bIdx(b), eIdx(e)
        {
            if (bIdx < setPtr->bucketCount && setPtr->buckets[bIdx].empty())
            {
                advance();
                if (bIdx >= setPtr->bucketCount)
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

        const T &operator*() const
        {
            return setPtr->buckets[bIdx][eIdx];
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

    void insert(const T &key)
    {
        if (contains(key))
            return;
        std::size_t index = getIndex(key);
        buckets[index].append(key);
    }

    bool contains(const T &key) const
    {
        std::size_t index = getIndex(key);
        const Array<T> &bucket = buckets[index];
        for (std::size_t i = 0; i < bucket.size(); i++)
        {
            if (bucket[i] == key)
                return true;
        }
        return false;
    }

    bool remove(const T &key)
    {
        std::size_t index = getIndex(key);
        Array<T> &bucket = buckets[index];

        for (std::size_t i = 0; i < bucket.size(); i++)
        {
            if (bucket[i] == key)
            {
                bucket.removeAt(i);
                return true;
            }
        }
        return false;
    }

    bool isEmpty() const
    {
        for (size_t i = 0; i < bucketCount; i++)
        {
            Array<T> &bucket = buckets[i];
            if (!bucket.empty())
            {
                return false;
            }
        }
        return true;
    }

    void clear()
    {
        for (size_t i = 0; i < bucketCount; i++)
        buckets[i].clear();
        {
            
        }
    }

    Array<T> getAllItems() const
    {
        Array<T> all;
        for (std::size_t i = 0; i < bucketCount; i++)
        {
            for (std::size_t j = 0; j < buckets[i].size(); j++)
            {
                all.append(buckets[i][j]);
            }
        }
        return all;
    }

private:
    std::size_t getIndex(const T &key) const
    {
        return hash(key) % bucketCount;
    }
};