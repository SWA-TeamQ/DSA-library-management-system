#pragma once
#include <string>
#include <iostream>
#include "dsa/Array.hpp"
#include "models/Transaction.hpp"
#include "dsa/HashTable.hpp"
#include "core/DataStore.hpp"
#include "TransactionSearch.hpp"

using namespace std;

class TransactionManager
{
private:
    DataStore<Transaction> transactionStore;
    HashTable<Transaction> transactionTable; // ID -> Transaction
    TransactionSearchMap searchMap;

public:
    TransactionManager(string filename) : transactionStore(filename)
    {
        loadTransactions();
    }

    bool loadTransactions()
    {
        transactionTable.clear();
        searchMap.clear();

        if (!transactionStore.loadData(transactionTable))
        {
            return false;
        }
        buildSearchMap();
        return true;
    }

    bool saveTransactions()
    {
        return transactionStore.saveData(transactionTable);
        
    }

    void buildSearchMap()
    {
        searchMap.buildIndices(transactionTable);
    }

    bool addTransaction(Transaction &t);
    bool removeTransaction(TransactionSearchKey key, string value);
    Transaction *findTransaction(TransactionSearchKey key, string value);
    Array<Transaction *> findTransactions(TransactionSearchKey key, string value);
    Array<Transaction *> sortTransactions(TransactionSortKey key, bool reverse = false);

    Array<Transaction *> getAllTransactions();
};
