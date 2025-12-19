#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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

    bool insert(const T &item)
    {
        string key = item.getKey();
        auto [it, inserted] = table.emplace(key, item);
        return inserted;
    }

    T *find(const string &key) const
    {
        auto it = table.find(key);
        if (it != table.end())
            return &it->second;
        return nullptr;
    }

    bool erase(const string &key)
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
        vector<T *> out;
        out.reserve(table.size());
        for (auto &[key, value] : table)
            out.push_back(&value);
        return out;
    }
};
