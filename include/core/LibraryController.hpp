#pragma once
#include <iostream>
#include <string>
#include "dsa/Array.hpp"
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
    BookManager bookManager;
    PatronManager patronManager;
    TransactionManager transactionManager;
    LoanService loanService;

public:
    LibraryController()
        : bookManager("books.txt"),
          patronManager("patrons.txt"),
          transactionManager("transactions.txt"),
          loanService(bookManager, patronManager, transactionManager)
    {}

    void load()
    {
        bookManager.loadBooks();
        patronManager.loadPatrons();
        transactionManager.loadTransactions();
    }

    void save()
    {
        bookManager.saveBooks();
        patronManager.savePatrons();
        transactionManager.saveTransactions();
    }

    // Book operations
    bool addBook( Book &b);
    bool removeBookById(const string &isbn);
    bool removeBookByTitle(const string &title);
    bool removeBookByAuthor(const string &author);
    bool removeBookByCategory(const string &category);
    Book *findBookById(const string &isbn);
    Array<Book *> findBooksByTitle(const string &title);
    Array<Book *> findBooksByAuthor(const string &author);
    Array<Book *> findBooksByCategory(const string &category);
    Array<Book *> sortBooksByTitle(bool reverse = false);
    Array<Book *> sortBooksByAuthor(bool reverse = false);
    Array<Book *> sortBooksByYear(bool reverse = false);
    Array<Book *> sortBooksByBorrowCount(bool reverse = false);

    bool updateBook( Book &b);
    Array<Book *> listAllBooks();

    // Patron operations
    bool addPatron( Patron &p);
    bool removePatronById(const string &patronID);
    bool removePatronByName(const string &patronName);
    Patron *findPatronById(const string &patronID);
    Patron *findPatronByName(const string &patronName);
    Array<Patron *> findPatronsById(const string &patronID);
    Array<Patron *> findPatronsByName(const string &patronName);
    Array<Patron *> sortPatronsByName(bool reverse = false);
    Array<Patron *> sortPatronsByMembershipDate(bool reverse = false);
    Array<Patron *> sortPatronsByBorrowCount(bool reverse = false);
    bool updatePatron( Patron &p);
    Array<Patron *> listAllPatrons() ;

    // Transaction operations
    bool addTransaction( Transaction &t);
    Array<Transaction *> listAllTransactions() ;
    void listTransactionsForPatron(const string &patronID);
    void listOverdueForPatron(const string &patronID);
    Array<Transaction *> sortTransactionsByReturnDate(bool reverse = false);

    // Borrow/Return operations
    bool borrowBook(const string &patronID, const string &isbn);
    bool returnBook(const string &patronID, const string &isbn);
};
