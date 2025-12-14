#include "managers/TransactionManager.hpp"
#include <algorithm>

void TransactionManager::loadTransactions()
{
    if (!store.loadData(transactionList))
    {
        cout << "Warning: Failed to load transactions from file\n";
        return;
    }
    for (auto &t : transactionList)
        transactions.insert(&t); // insert into hash table
}

void TransactionManager::saveTransactions()
{
    if (!store.saveData(transactionList))
    {
        cout << "Warning: Failed to save transactions to file\n";
    }
}

bool TransactionManager::addTransaction(const Transaction &t)
{
    transactionList.push_back(t);
    if (transactions.insert(&transactionList.back()))
    {
        if (!store.addData(transactionList.back()))
        {
            transactions.erase(transactionList.back().getTransactionID());
            transactionList.pop_back();
            return false;
        }
        return true;
    }
    else
    {
        transactionList.pop_back();
        return false;
    }
}

bool TransactionManager::removeTransaction(const string &transactionID)
{
    transactions.erase(transactionID);
    auto it = std::find_if(transactionList.begin(), transactionList.end(), [&](const Transaction &tr)
                           { return tr.getTransactionID() == transactionID; });
    if (it != transactionList.end())
        transactionList.erase(it);
    saveTransactions(); // persist after removal
    return true;
}

Transaction *TransactionManager::findTransaction(const string &transactionID)
{
    return transactions.find(transactionID);
}

void TransactionManager::displayAll() const
{
    cout << "--- Transactions ---\n";
    for (auto *t : transactions.all())
        t->displayDetails();
}

vector<Transaction*> TransactionManager::getAllTransactions() const
{
    return transactions.all();
}
