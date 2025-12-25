#pragma once
#include "models/Patron.hpp"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "dsa/Array.hpp"

using namespace std;

class PatronSearchMap
{
private:
    unordered_map<string, unordered_set<string>> nameIndex;

public:
    PatronSearchMap() = default;
    ~PatronSearchMap() = default;

    void clear()
    {
        nameIndex.clear();
    }

    void buildIndices(HashTable<Patron> &patrons)
    {
        clear();
        for (auto &[id, p] : patrons)
        {
            insert(p);
        }
    }

    void insert(Patron &p)
    {
        nameIndex[p.getName()].insert(p.getKey());
    }

    void remove(Patron &p)
    {
        string id = p.getKey(), name = p.getName();

        auto it = nameIndex.find(name);
        if (it != nameIndex.end())
        {
            it->second.erase(id);
            if (it->second.empty())
            {
                nameIndex.erase(it);
            }
        }
    }

    // Search patrons by name
    Array<string> findByName(string name)
    {
        auto it = nameIndex.find(name);
        if (it != nameIndex.end())
        {
            auto setIt = it->second;
            Array<string> ids;
            for (auto &key : setIt)
            {
                ids.append(key);
            }
            return ids;
        }
        return {};
    }
};
