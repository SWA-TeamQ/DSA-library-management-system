#pragma once
#include "models/Transaction.hpp"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

// Simple search table for Transactions by book and patron IDs
class TransactionSearchMap
{
private:
    unordered_map<string, unordered_set<string>> bookIdIndex;
    unordered_map<string, unordered_set<string>> patronIdIndex;

public:
    TransactionSearchMap() = default;
    ~TransactionSearchMap() = default;

    void clear(){
        bookIdIndex.clear();
        patronIdIndex.clear();
    }

    // Build indices from any container of Transactions (e.g., vector, HashTable)
    template <typename Container>
    void buildIndices(const Container& transactions)
    {
        clear();
        for(const auto &entry : transactions){
            insert(entry.second);
        }
    }

    void insert(const Transaction& t)
    {
        bookIdIndex[t.getBookID()].insert(t.getKey());
        patronIdIndex[t.getPatronID()].insert(t.getKey());
    }

    void remove(const Transaction& t)
    {
        string id = t.getKey(), bookId = t.getBookID(), patronId = t.getPatronID();

        auto it = bookIdIndex.find(bookId);
        if(it != bookIdIndex.end()){
            it->second.erase(id);
            if(it->second.empty()){
                bookIdIndex.erase(it);
            }
        }
        
        it = patronIdIndex.find(patronId);
        if(it != patronIdIndex.end()){
            it->second.erase(id);
            if(it->second.empty()){
                patronIdIndex.erase(it);
            }
        }
    }

    // Search transactions by bookId
    vector<string> findByBookId(const string& bookId) const
    {
        auto it = bookIdIndex.find(bookId);
        if (it != bookIdIndex.end())
            return vector<string>(it->second.begin(), it->second.end());
        return {};
    }

    // Search transactions by patronId
    vector<string> findByPatronId(const string& patronId) const
    {
        auto it = patronIdIndex.find(patronId);
        if (it != patronIdIndex.end())
            return vector<string>(it->second.begin(), it->second.end());
        return {};
    }
};
