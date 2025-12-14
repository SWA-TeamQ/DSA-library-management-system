#include "managers/TransactionManager.hpp"
#include <algorithm>

void TransactionManager::loadTransactions()
{
    store.loadData(transactions);
}

void TransactionManager::saveTransactions() const
{
    store.saveData(transactions);
}

void TransactionManager::add(const Transaction &t)
{
    transactions.push_back(t);
    store.addData(t);
}

void TransactionManager::remove(const string &transactionID)
{
    for (auto it = transactions.begin(); it != transactions.end(); ++it)
    {
        if (it != transactions.end())
        {
            transactions.erase(it);
            saveTransactions(); // Save after removal
        }
    }
}

void TransactionManager::displayAll() const
{
    for (const auto &transaction : transactions)
    {
        transaction.displayDetails();
    }
}
