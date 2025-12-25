#pragma once
#include <iostream>
#include <iomanip>
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

    bool borrowBook(string patronID, string isbn);
    bool returnBook(string patronID, string isbn);
};