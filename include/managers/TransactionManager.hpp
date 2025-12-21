#pragma once
#include <vector>
#include "models/Transaction.hpp"
#include "dsa/HashTable.hpp"
#include "core/DataStore.hpp"

class TransactionManager
{
private:
    HashTable<Transaction> transactions; // Hash table keyed by transactionID
    vector<Transaction> transactionList;
    DataStore<Transaction> store;

public:
    TransactionManager(const string &filename) : store(filename)
    {
        loadTransactions();
    }

    void loadTransactions();
    void saveTransactions();

    bool addTransaction(const Transaction &t);
    bool removeTransaction(TransactionSearchKey key);
    Transaction *findTransaction(TransactionSearchKey key);
    vector<Transaction *> findTransactions(TransactionSearchKey key);
    void sortTransactions(TransactionSortKey key, bool reverse = false);
    bool updateTransaction(TransactionSearchKey key);

    
    void listAllTransactions() const;
};
