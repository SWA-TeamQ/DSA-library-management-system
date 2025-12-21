#include "managers/TransactionManager.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

void TransactionManager::addTransaction(const Transaction &t)
{
    int index = transactionList.size();
    transactionList.push_back(t);
    transactionTable.insert(t.getKey(), index);
    searchMap.insert(t);
    transactionStore.addData(t);
}

bool TransactionManager::removeTransaction(const TransactionSearchKey key, const string &value)
{
    vector<string> ids;
    switch (key)
    {
    case TransactionSearchKey::ID:
        ids.push_back(value);
        break;
    case TransactionSearchKey::BOOK_ID:
        ids = searchMap.findByBookId(value);
        break;
    case TransactionSearchKey::PATRON_ID:
        ids = searchMap.findByPatronId(value);
        break;
    }

    if (ids.empty()) return false;

    bool deleted = false;
    for (const string &id : ids)
    {
        int *indexPtr = transactionTable.find(id);
        if (indexPtr)
        {
            int index = *indexPtr;
            Transaction t = transactionList[index]; 
            transactionList.erase(transactionList.begin() + index);
            searchMap.remove(t);
            deleted = true;
        }
    }
    
    if (deleted)
    {
        buildSearchIndex();
        saveTransactions();
    }
    return deleted;
}

Transaction *TransactionManager::findTransaction(const TransactionSearchKey key, const string &value) const
{
    vector<string> ids;
    switch (key)
    {
    case TransactionSearchKey::ID:
        ids.push_back(value);
        break;
    case TransactionSearchKey::BOOK_ID:
        ids = searchMap.findByBookId(value);
        break;
    case TransactionSearchKey::PATRON_ID:
        ids = searchMap.findByPatronId(value);
        break;
    }

    if (ids.empty()) return nullptr;

    int *indexPtr = transactionTable.find(ids[0]);
    return &transactionList[*indexPtr];
}

vector<Transaction *> TransactionManager::findTransactions(const TransactionSearchKey key, const string &value) const
{
    vector<string> ids;
    switch (key)
    {
    case TransactionSearchKey::ID:
        ids.push_back(value);
        break;
    case TransactionSearchKey::BOOK_ID:
        ids = searchMap.findByBookId(value);
        break;
    case TransactionSearchKey::PATRON_ID:
        ids = searchMap.findByPatronId(value);
        break;
    }

    vector<Transaction *> results;
    for (const string &id : ids)
    {
        int *indexPtr = transactionTable.find(id);
        results.push_back(&transactionList[*indexPtr]);
    }
    return results;
}

void TransactionManager::sortTransactions(TransactionSortKey key, bool reverse)
{
    switch (key)
    {
    case TransactionSortKey::BORROW_DATE:
        mergeSort(transactionList, [](const Transaction &t){
            return t.getBorrowDate();
        }, reverse);
        break;
    case TransactionSortKey::RETURN_DATE:
        mergeSort(transactionList, [](const Transaction &t){
            return t.getReturnDate();
        }, reverse);
        break;
    }
}

vector<Transaction *> TransactionManager::getAllTransactions() const
{
    vector<Transaction *> results;
    for (const auto &t : transactionList)
    {
        results.push_back(&t);
    }
    return results;
}