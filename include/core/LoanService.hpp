#pragma once
#include <string>
#include "managers/BookManager.hpp"
#include "managers/PatronManager.hpp"
#include "managers/TransactionManager.hpp"
#include "utils/utils.hpp"

using namespace std;

class LoanService
{
private:
    BookManager &bookManager;
    PatronManager &patronManager;
    TransactionManager &transactionManager;

public:
    LoanService(BookManager &bm, PatronManager &pm, TransactionManager &tm)
        : bookManager(bm), patronManager(pm), transactionManager(tm) {}

    bool borrowBook(const string &patronID, const string &isbn);
    bool returnBook(const string &patronID, const string &isbn);
};