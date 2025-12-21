#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "models/Transaction.hpp"
#include "dsa/HashTable.hpp"
#include "core/DataStore.hpp"
#include "TransactionSearch.hpp"

using namespace std;

class TransactionManager
{
private:
    DataStore<string, Transaction> transactionStore;
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
    vector<Transaction *> findTransactions(const TransactionSearchKey key, const string &value) const;
    vector<Transaction *> sortTransactions(const TransactionSortKey key, bool reverse = false);

    vector<Transaction *> getAllTransactions() const;
};
