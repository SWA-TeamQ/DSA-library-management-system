#include "managers/TransactionManager.hpp"
#include <algorithm>
#include <iostream>
#include "dsa/MergeSort.hpp"

using namespace std;

bool TransactionManager::addTransaction(const Transaction &t)
{
    transactionTable[t.getKey()] = t;
    searchMap.insert(t);
    transactionStore.addData(t);
    return true;
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
        Transaction *t = transactionTable.find(id);
        if(!t) continue;
        searchMap.remove(*t);
        transactionTable.remove(id);
        deleted = true;
    }
    
    if (deleted)
    {
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

    Transaction *t = transactionTable.find(ids[0]);
    return t;
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
        Transaction *t = transactionTable.find(id);
        if (t) results.push_back(t);
    }
    return results;
}

vector<Transaction *> TransactionManager::sortTransactions(TransactionSortKey key, bool reverse)
{
    vector<Transaction *> sorted = transactionTable.all();

    switch (key)
    {
    case TransactionSortKey::BORROW_DATE:
        mergeSort(sorted, [](const Transaction *t){
            return t->getBorrowDate();
        }, reverse);
        break;
    case TransactionSortKey::DUE_DATE:
        mergeSort(sorted, [](const Transaction *t){
            return t->getDueDate();
        }, reverse);
        break;
    case TransactionSortKey::RETURN_DATE:
        mergeSort(sorted, [](const Transaction *t){
            return t->getReturnDate();
        }, reverse);
        break;
    }
    return sorted;
}

vector<Transaction *> TransactionManager::getAllTransactions() const
{
    return transactionTable.all();
}