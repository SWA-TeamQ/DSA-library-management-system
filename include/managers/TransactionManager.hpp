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
    HashTable<string, Transaction> transactionTable; // ID -> Transaction
    TransactionSearchMap searchMap;

public:
    TransactionManager(const string &filename) : transactionStore(filename)
    {
        loadTransactions();
    }

    void loadTransactions(){
        transactionTable.clear();
        searchMap.clear();

        if(!transactionStore.loadData(transactionTable)){
            cout << "Warning: Failed to load transactions from file\n";
            return;
        }
        buildSearchMap();
    }

    void saveTransactions(){
        if(!transactionStore.saveData(transactionTable)){
            cout << "Warning: Failed to save transactions to file\n";
        }
    }

    void buildSearchMap(){
        searchMap.buildIndices(transactionTable);
    }

    bool addTransaction(const Transaction &t);
    bool removeTransaction(const TransactionSearchKey key, const string &value);
    Transaction *findTransaction(const TransactionSearchKey key, const string &value) const;
    Array<Transaction *> findTransactions(const TransactionSearchKey key, const string &value) const;
    Array<Transaction *> sortTransactions(const TransactionSortKey key, bool reverse = false);

    Array<Transaction *> getAllTransactions() const;
};
