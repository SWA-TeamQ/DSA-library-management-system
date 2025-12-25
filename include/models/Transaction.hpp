#pragma once
#include <string>
#include <iostream>
#include "dsa/Array.hpp"

using namespace std;

enum class TransactionSearchKey { ID, BOOK_ID, PATRON_ID };
enum class TransactionSortKey { BORROW_DATE, DUE_DATE, RETURN_DATE };

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
                bool returned = false)
    {
        this->transactionID = transactionID;
        this->bookID = bookID;
        this->patronID = patronID;
        this->borrowDate = borrowDate;
        this->dueDate = dueDate;
        this->returnDate = returnDate;
        this->returned = returned;
    }

    // for generic lookup
    const string& getKey() const { return transactionID; }

    string &getID()  { return transactionID; }
    const string& getBookID() const { return bookID; }
    const string& getPatronID() const { return patronID; }
    string &getBorrowDate()  { return borrowDate; }
    string &getDueDate()  { return dueDate; }
    string &getReturnDate()  { return returnDate; }
    bool isReturned()  { return returned; }

    void setId(const string &id) { transactionID = id; }
    void setBookID(const string &id) { bookID = id; }
    void setPatronID(const string &id) { patronID = id; }
    void setBorrowDate(const string &date) { borrowDate = date; }
    void setDueDate(const string &date) { dueDate = date; }
    void setReturnDate(const string &date) { returnDate = date; }
    void setReturned(bool r) { returned = r; }

    bool isOverdue() ;
    void markReturned();
    double calculateFine(double dailyRate = 0.50) ;

    string serialize() const ;
    void deserialize(const string &line);

    Array<string> getFields() ;
    Array<string> getValues() ;
};
