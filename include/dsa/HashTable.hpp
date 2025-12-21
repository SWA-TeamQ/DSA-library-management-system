#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

template <typename U, typename T>
class HashTable
{
private:
    unordered_map<U, T> table;

public:
    HashTable() = default;
    ~HashTable() = default;

    bool empty() const
    {
        return table.empty();
    }

    size_t size() const
    {
        return table.size();
    }

    bool insert(const U &key, const T &item)
    {
        auto [it, inserted] = table.emplace(key, item);
        return inserted;
    }

    T *find(const U &key) const
    {
        auto it = table.find(key);
        if (it != table.end())
            return &it->second;
        return nullptr;
    }

    bool remove(const U &key)
    {
        auto removed = table.erase(key);
        return removed > 0;
    }

    void clear()
    {
        table.clear();
    }

    vector<T *> all() const
    {
        vector<T *> result;
        result.reserve(table.size());
        for (auto &[key, value] : table)
            result.push_back(&value);
        return result;
    }
};
