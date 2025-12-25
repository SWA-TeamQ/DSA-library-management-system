#pragma once
#include <string>
#include <iostream>
#include "dsa/Array.hpp"

using namespace std;

enum class TransactionSearchKey
{
    ID,
    BOOK_ID,
    PATRON_ID
};
enum class TransactionSortKey
{
    BORROW_DATE,
    DUE_DATE,
    RETURN_DATE
};

class Transaction
{
private:
    string transactionID;
    string bookID;
    string patronID;
    string borrowDate;
    string dueDate;
    string returnDate;
    bool returned{false};

public:
    Transaction() = default;

    Transaction(string transactionID,
                string bookID,
                string patronID,
                string borrowDate,
                string dueDate,
                string returnDate,
                bool returned = false) : transactionID(transactionID),
                                         bookID(bookID),
                                         patronID(patronID),
                                         borrowDate(borrowDate),
                                         dueDate(dueDate),
                                         returnDate(returnDate),
                                         returned(returned)
    {
    }

    // for generic lookup
    string getKey() { return transactionID; }

    string getID() { return transactionID; }
    string getBookID() { return bookID; }
    string getPatronID() { return patronID; }
    string getBorrowDate() { return borrowDate; }
    string getDueDate() { return dueDate; }
    string getReturnDate() { return returnDate; }
    bool isReturned() { return returned; }

    void setId(string id) { transactionID = id; }
    void setBookID(string id) { bookID = id; }
    void setPatronID(string id) { patronID = id; }
    void setBorrowDate(string date) { borrowDate = date; }
    void setDueDate(string date) { dueDate = date; }
    void setReturnDate(string date) { returnDate = date; }
    void setReturned(bool r) { returned = r; }

    bool isOverdue();
    void markReturned();
    double calculateFine(double dailyRate = 0.50);

    string serialize();
    void deserialize(string line);

    Array<string> getFields();
    Array<string> getValues();
};
