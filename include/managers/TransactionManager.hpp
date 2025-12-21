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
    vector<Transaction> transactionList;
    HashTable<string, int> transactionTable; // ID -> index
    TransactionSearchMap searchMap;
    DataStore<Transaction> transactionStore;

public:
    TransactionManager(const string &filename) : transactionStore(filename)
    {
        loadTransactions();
    }

    void loadTransactions()
    {
        transactionList.clear();
        transactionTable.clear();
        searchMap.clear();
    
        if (!transactionStore.loadData(transactionList))
        {
            cout << "Warning: Failed to load transactions from file\n";
            return;
        }
        buildSearchIndex();
        buildSearchMap();
    }

    void saveTransactions(){
        if(!transactionStore.saveData(transactionList)){
            cout << "Warning: Failed to save transactions to file\n";
        }
    }

    void buildSearchIndex(){
        transactionTable.clear();
        for (int i = 0; i < (int)transactionList.size(); i++)
            transactionTable.insert(transactionList[i].getKey(), i);
    }

    void buildSearchMap(){
        searchMap.buildIndices(transactionList);
    }

    void addTransaction(const Transaction &t);
    bool removeTransaction(const TransactionSearchKey key, const string &value);
    Transaction *findTransaction(const TransactionSearchKey key, const string &value) const;
    vector<Transaction *> findTransactions(const TransactionSearchKey key, const string &value) const;
    void sortTransactions(const TransactionSortKey key, bool reverse = false);

    vector<Transaction *> getAllTransactions() const;
};
