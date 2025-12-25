#include "managers/TransactionManager.hpp"
#include <algorithm>
#include <iostream>
#include "dsa/MergeSort.hpp"

using namespace std;

bool TransactionManager::addTransaction(Transaction &t)
{
    transactionTable[t.getKey()] = t;
    searchMap.insert(t);
    transactionStore.addData(t);
    return true;
}

bool TransactionManager::removeTransaction(TransactionSearchKey key, string value)
{
    Array<string> ids;
    switch (key)
    {
    case TransactionSearchKey::ID:
        ids.append(value);
        break;
    case TransactionSearchKey::BOOK_ID:
        ids = searchMap.findByBookId(value);
        break;
    case TransactionSearchKey::PATRON_ID:
        ids = searchMap.findByPatronId(value);
        break;
    }

    if (ids.empty())
        return false;

    bool deleted = false;
    for (string &id : ids)
    {
        Transaction *t = transactionTable.find(id);
        if (!t)
            continue;
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

Transaction *TransactionManager::findTransaction(TransactionSearchKey key, string value)
{
    Array<string> ids;
    switch (key)
    {
    case TransactionSearchKey::ID:
        ids.append(value);
        break;
    case TransactionSearchKey::BOOK_ID:
        ids = searchMap.findByBookId(value);
        break;
    case TransactionSearchKey::PATRON_ID:
        ids = searchMap.findByPatronId(value);
        break;
    }

    if (ids.empty())
        return nullptr;

    Transaction *t = transactionTable.find(ids[0]);
    return t;
}

Array<Transaction *> TransactionManager::findTransactions(TransactionSearchKey key, string value)
{
    Array<string> ids;
    switch (key)
    {
    case TransactionSearchKey::ID:
        ids.append(value);
        break;
    case TransactionSearchKey::BOOK_ID:
        ids = searchMap.findByBookId(value);
        break;
    case TransactionSearchKey::PATRON_ID:
        ids = searchMap.findByPatronId(value);
        break;
    }

    Array<Transaction *> results;
    for (string &id : ids)
    {
        Transaction *t = transactionTable.find(id);
        if (t)
        {
            results.append(t);
        }
    }
    return results;
}

Array<Transaction *> TransactionManager::sortTransactions(TransactionSortKey key, bool reverse)
{
    Array<Transaction *> sorted = transactionTable.all();

    switch (key)
    {
    case TransactionSortKey::BORROW_DATE:
        mergeSort(sorted, [](Transaction *t)
                  { return t->getBorrowDate(); }, reverse);
        break;
    case TransactionSortKey::DUE_DATE:
        mergeSort(sorted, [](Transaction *t)
                  { return t->getDueDate(); }, reverse);
        break;
    case TransactionSortKey::RETURN_DATE:
        mergeSort(sorted, [](Transaction *t)
                  { return t->getReturnDate(); }, reverse);
        break;
    }
    return sorted;
}

Array<Transaction *> TransactionManager::getAllTransactions()
{
    return transactionTable.all();
}
