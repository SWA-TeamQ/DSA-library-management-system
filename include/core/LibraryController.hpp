#pragma once
#include <vector>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "dsa/HashTable.hpp"
#include "managers/BookManager.hpp"
#include "managers/TransactionManager.hpp"
#include "managers/PatronManager.hpp"
#include "core/LoanService.hpp"

using namespace std;

class LibraryController
{
private:
    PatronManager patronsManager("patrons.txt");
    BookManager booksManager("books.txt");
    TransactionManager transactionsManager("transactions.txt");
    LoanService loanService;

public:
    LibraryController()
    {
        loanService(booksManager, patronsManager, transactionsManager)
    }

    void load()
    {
        patronsManager.loadPatrons();
        booksManager.loadBooks();
        transactionsManager.loadTransactions();
    }

    void save()
    {
        patronsManager.savePatrons();
        booksManager.saveBooks();
        transactionsManager.saveTransactions();
    }

    // Book operations

    bool addBook(const Book &b);
    bool removeBookByISBN(const string &isbn);
    Book *findBook(const string &isbn);

    Book *findBook(const string &searchString) const;
    vector<Book *> findBooks(const string &searchString) const;
    void sortBooks(const string &sortString, bool reverse = false);
    bool updateBook(const string &updateString);
    void listAllBooks() const;


    // Patron operations
    bool addPatron(const Patron &p);
    Patron *findPatron(const string &searchString);
    vector<Patron *> findPatrons(const string &searchString);
    void sortPatrons(const string &sortString, bool reverse = false);
    bool updatePatron(const string &updateString);
    void listAllPatrons() const;

    // Borrow/Return operations
    bool borrowBook(const string &patronID, const string &isbn);
    bool returnBook(const string &patronID, const string &isbn);

    // Reporting
    void listAllPatrons() const;
    void listAllTransactions() const;
};
