#pragma once
#include <vector>
#include <string>
#include <memory>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "managers/BookManager.hpp"
#include "managers/TransactionManager.hpp"
#include "managers/PatronManager.hpp"
#include "core/LoanService.hpp"

using namespace std;

class LibraryController
{
private:
    BookManager booksManager;
    PatronManager patronsManager;
    TransactionManager transactionsManager;
    LoanService loanService;

public:
    LibraryController() 
        : booksManager("books.txt"),
          patronsManager("patrons.txt"),
          transactionsManager("transactions.txt"),
          loanService(booksManager, patronsManager, transactionsManager)
    {
    }

    void load()
    {
        booksManager.loadBooks();
        patronsManager.loadPatrons();
        transactionsManager.loadTransactions();
    }

    void save()
    {
        booksManager.saveBooks();
        patronsManager.savePatrons();
        transactionsManager.saveTransactions();
    }

    // Book operations
    bool addBook(const Book &b);
    bool removeBook(const string &isbn);
    Book *findBook(const string &isbn) const;
    vector<Book *> findBooksByTitle(const string &title) const;
    vector<Book *> findBooksByAuthor(const string &author) const;
    vector<Book *> sortBooks(BookSortKey key, bool reverse = false);
    bool updateBook(const Book &b);
    void listAllBooks() const;

    // Patron operations
    bool addPatron(const Patron &p);
    bool removePatron(const string &patronID);
    Patron *findPatron(const string &patronID) const;
    vector<Patron *> sortPatrons(PatronSortKey key, bool reverse = false);
    bool updatePatron(const Patron &p);
    void listAllPatrons() const;

    // Transaction operations
    bool addTransaction(const Transaction &t);
    void listAllTransactions() const;

    // Borrow/Return operations
    bool borrowBook(const string &patronID, const string &isbn);
    bool returnBook(const string &patronID, const string &isbn);
};
