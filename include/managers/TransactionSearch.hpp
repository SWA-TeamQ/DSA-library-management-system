#pragma once
#include "models/Transaction.hpp"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "dsa/Array.hpp"

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

    void clear()
    {
        bookIdIndex.clear();
        patronIdIndex.clear();
    }

    void buildIndices(HashTable<Transaction> &transactions)
    {
        clear();
        for (auto &entry : transactions)
        {
            insert(entry.second);
        }
    }

    void insert(Transaction &t)
    {
        bookIdIndex[t.getBookID()].insert(t.getKey());
        patronIdIndex[t.getPatronID()].insert(t.getKey());
    }

    void remove(Transaction &t)
    {
        string key = t.getKey(), patronId = t.getPatronID(), bookId = t.getBookID();

        removeIndex(bookIdIndex, key, bookId);
        removeIndex(patronIdIndex, key, patronId);
    }

    // Search transactions by bookId
    Array<string> findByBookId(string bookId)
    {
        return findIds(bookIdIndex, bookId);
    }

    // Search transactions by patronId
    Array<string> findByPatronId(string patronId)
    {
        return findIds(patronIdIndex, patronId);
    }
};
