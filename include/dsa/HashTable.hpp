#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "dsa/Array.hpp"

using namespace std;

template <typename T>
class HashTable
{
private:
    unordered_map<string, T> table;

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

    bool insert(const string &key, T &item)
    {
        auto [it, inserted] = table.emplace(key, item);
        return inserted;
    }

    T &operator[](const string &key)
    {
        return table[key];
    }

    auto begin() { return table.begin(); }
    auto end() { return table.end(); }

    T* find(const string &key)
    {
    auto it = table.find(key);
    if (it != table.end())
        return &it->second;
    return nullptr;
    }

    bool remove(const string &key)
    {
        auto removed = table.erase(key);
        return removed > 0;
    }

    void clear()
    {
        table.clear();
    }

    Array<T *> all()
    {
        Array<T *> result = Array<T *>(table.size());
        
        for (auto &[key, value] : table)
            result.append(&value);
        return result;
    }
};

