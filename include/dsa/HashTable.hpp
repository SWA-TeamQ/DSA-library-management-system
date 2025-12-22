#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "dsa/Array.hpp"

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

    T &operator[](const U &key)
    {
        return table[key];
    }

    const T &operator[](const U &key) const
    {
        return table.at(key);
    }

    auto begin() { return table.begin(); }
    auto end() { return table.end(); }
    auto begin() const { return table.begin(); }
    auto end() const { return table.end(); }

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

    Array<T *> all() const
    {
        Array<T *> result = Array<T *>(table.size());
        
        for (auto &[key, value] : table)
            result.push_back(&value);
        return result;
    }
};
