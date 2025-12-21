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
    {
        booksManager = BookManager("books.txt");
        patronsManager = PatronManager("patrons.txt");
        transactionsManager = TransactionManager("transactions.txt");
        loanService = LoanService(booksManager, patronsManager, transactionsManager);
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
    void sortBooks(BookSortKey key, bool reverse = false);
    bool updateBook(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount);
    void listAllBooks() const;

    // Patron operations
    bool addPatron(const Patron &p);
    bool removePatron(const string &patronID);
    Patron *findPatron(const string &patronID) const;
    void sortPatrons(PatronSortKey key, bool reverse = false);
    bool updatePatron(const string &patronID, const string &name, const string &contact, const string &membershipDate, int borrowCount);
    void listAllPatrons() const;

    // Transaction operations
    void listAllTransactions() const;

    // Borrow/Return operations
    bool borrowBook(const string &patronID, const string &isbn);
    bool returnBook(const string &patronID, const string &isbn);
};
