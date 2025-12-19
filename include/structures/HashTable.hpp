#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

template <typename T>
class HashTable
{
private:
    std::unordered_map<std::string, T *> table;

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

    bool insert(T *item)
    {
        if (!item)
            return false;
        std::string key = item->getKey();
        auto [it, inserted] = table.emplace(key, item);
        return inserted;
    }

    T* find(const std::string &key) const
    {
        auto it = table.find(key);
        if(it != table.end())
            return it->second;
        return nullptr;
    }

    bool erase(const std::string &key)
    {
        auto removed = table.erase(key);
        return removed > 0;
    }

    void clear()
    {
        table.clear();
    }

    std::vector<T *> all() const
    {
        std::vector<T *> out;
        out.reserve(table.size());
        for (auto &[key, value] : table)
            out.push_back(value);
        return out;
    }
};
