#pragma once
#include <string>
#include <chrono>
#include <iostream>
using namespace std;

class Transaction {
private:
    string transactionID;
    string bookID; // ISBN
    string patronID;
    chrono::system_clock::time_point borrowDate{chrono::system_clock::now()};
    chrono::system_clock::time_point dueDate{borrowDate + chrono::hours(24 * 14)}; // 2 weeks
    chrono::system_clock::time_point returnDate{}; // epoch -> not returned yet
    bool returned{false};
public:
    Transaction() = default;
    Transaction(string tx, string b, string p)
        : transactionID(move(tx)), bookID(move(b)), patronID(move(p)) {}

    const string& getTransactionID() const { return transactionID; }
    const string& getBookID() const { return bookID; }
    const string& getPatronID() const { return patronID; }
    chrono::system_clock::time_point getBorrowDate() const { return borrowDate; }
    chrono::system_clock::time_point getDueDate() const { return dueDate; }
    bool isReturned() const { return returned; }
    bool isOverdue() const;

    void markReturned();
    double calculateFine(double dailyRate = 0.50) const; // simplistic fine calc
    void display(ostream& os = cout) const;
};
