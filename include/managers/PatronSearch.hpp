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

    void clear(){
        nameIndex.clear();
    }

    // Build indices from any map-like container of Patrons (e.g., unordered_map, HashTable)
    template <typename MapType>
    void buildIndices(const MapType& patrons)
    {
        clear();
        for(const auto &[id, p] : patrons){
            insert(p);
        }
    }

    void insert(const Patron& p)
    {
        nameIndex[p.getName()].insert(p.getKey());
    }

    void remove(const Patron& p)
    {
        string id = p.getKey(), name = p.getName();
        
        auto it = nameIndex.find(name);
        if(it != nameIndex.end()){
            it->second.erase(id);
            if(it->second.empty()){
                nameIndex.erase(it);
            }
        }
    }

    // Search patrons by name
    Array<string> findByName(const string& name) const
    {
        auto it = nameIndex.find(name);
        if (it != nameIndex.end()){
            auto setIt = it->second;
            Array<string> ids;
            for(auto &key : setIt){
                ids.append(key);
            }
            return ids;
        }
        return {};
    }
};
