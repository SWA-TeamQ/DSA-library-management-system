#pragma once
#include <string>
#include <iostream>
using namespace std;

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

    Transaction(string transactionID = "",
                string bookID = "",
                string patronID = "",
                string borrowDate = "",
                string dueDate = "",
                string returnDate = "",
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

    const string &getTransactionID() const { return transactionID; }
    const string &getBookID() const { return bookID; }
    const string &getPatronID() const { return patronID; }
    const string &getBorrowDate() const { return borrowDate; }
    const string &getDueDate() const { return dueDate; }
    const string &getReturnDate() const { return returnDate; }
    bool isReturned() const { return returned; }

    void setTransactionID(const string &id) { transactionID = id; }
    void setBookID(const string &id) { bookID = id; }
    void setPatronID(const string &id) { patronID = id; }
    void setBorrowDate(const string &date) { borrowDate = date; }
    void setDueDate(const string &date) { dueDate = date; }
    void setReturnDate(const string &date) { returnDate = date; }
    void setReturned(bool r) { returned = r; }

    bool isOverdue() const;
    void markReturned();
    double calculateFine(double dailyRate = 0.50) const;

    void displayDetails();
    string serialize() const;
    void deserialize(const string &line);
};
