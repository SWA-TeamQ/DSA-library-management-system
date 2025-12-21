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
    PatronManager patronsManager;
    BookManager booksManager;
    TransactionManager transactionsManager;
    LoanService loanService;

public:
    LibraryController()
    {
        bookManager = BookManager("books.txt");
        patronManager = PatronManager("patrons.txt");
        transactionManager = TransactionManager("transactions.txt");
        loanService(booksManager, patronsManager, transactionsManager);
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
    bool removeBook(BookSearchKey key);

    Book *findBook(BookSearchKey key) const;
    vector<Book *> findBooks(BookSearchKey key) const;
    void sortBooks(BookSortKey key, bool reverse = false);
    bool updateBook(BookAllKey key);
    void listAllBooks() const;


    // Patron operations
    bool addPatron(const Patron &p);
    bool removePatron(PatronSearchKey key);
    Patron *findPatron(PatronSearchKey key);
    vector<Patron *> findPatrons(PatronSearchKey key);
    void sortPatrons(PatronSortKey key, bool reverse = false);
    bool updatePatron(PatronAllKey key);
    void listAllPatrons() const;

    // Transaction operations
    bool addTransaction(const Transaction &t);
    bool removeTransaction(TransactionSearchKey key);
    Transaction *findTransaction(TransactionSearchKey key);
    vector<Transaction *> findTransactions(TransactionSearchKey key);
    void sortTransactions(TransactionSortKey key, bool reverse = false);
    bool updateTransaction(TransactionAllKey key);
    void listAllTransactions() const;

    // Borrow/Return operations
    bool borrowBook(const string &patronID, const string &isbn);
    bool returnBook(const string &patronID, const string &isbn);

    // Reporting
    void listAllBooks() const;
    void listAllPatrons() const;
    void listAllTransactions() const;
};
