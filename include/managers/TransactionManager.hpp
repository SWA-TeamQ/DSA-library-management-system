#pragma once
#include <vector>
#include "models/Transaction.hpp"
#include "core/DataStore.hpp"

class TransactionManager
{
private:
    vector<Transaction> transactions;
    DataStore<Transaction> store;

public:
    TransactionManager(const string &filename) : store(filename)
    {
        loadTransactions();
    }

    void loadTransactions();
    void saveTransactions() const;

    void add(const Transaction &t);
    void remove(const string &transactionID);

    void displayAll() const;
};
