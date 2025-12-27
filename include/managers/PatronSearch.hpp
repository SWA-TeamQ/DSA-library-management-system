#pragma once
#include "models/Patron.hpp"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "dsa/Array.hpp"
#include "utils/utils.hpp"

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
        string name = toLower(p.getName());
        nameIndex[name].insert(p.getKey());
    }

    void remove(Patron &p)
    {
        string key = p.getKey(), name = p.getName();

        removeIndex(nameIndex, key, name);
    }

    // Search patrons by name
    Array<string> findByName(string name)
    {
        Array<string> result;
        findIds(nameIndex, name, result);
        return result;
    }
};
