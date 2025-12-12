#pragma once
#include <vector>
#include <string>
#include "Book.hpp"
#include "Patron.hpp"
#include "Transaction.hpp"
#include "HashTable.hpp"
using namespace std;

class LibraryController {
private:
    BookHashTable books; // Hash table keyed by ISBN
    vector<Patron> patrons;
    vector<Transaction> transactions;

    void createTransaction(const string& patronID, const string& isbn);
    void markLatestReturned(const string& patronID, const string& isbn);
public:
    LibraryController() = default;

    // Book operations
    bool addBook(const Book& b);
    bool removeBookByISBN(const string& isbn);
    Book* findBookByISBN(const string& isbn);

    // Patron operations
    bool addPatron(const Patron& p);
    Patron* findPatronByID(const string& id);

    // Borrow/Return operations
    bool borrowBook(const string& patronID, const string& isbn);
    bool returnBook(const string& patronID, const string& isbn);

    // Reporting stubs
    void listAllBooks() const;
    void listAllPatrons() const;
};
