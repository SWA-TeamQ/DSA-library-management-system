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
#include "ui/UiHelpers.hpp"

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
    {
    }

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
    bool addBook(Book &b);
    bool removeBookById(string isbn);
    bool removeBookByTitle(string title);
    bool removeBookByAuthor(string author);
    bool removeBookByCategory(string category);
    Book *findBookById(string isbn);
    Array<Book *> findBooksByTitle(string title);
    Array<Book *> findBooksByAuthor(string author);
    Array<Book *> findBooksByCategory(string category);
    Array<Book *> sortBooksByTitle(bool reverse = false);
    Array<Book *> sortBooksByAuthor(bool reverse = false);
    Array<Book *> sortBooksByYear(bool reverse = false);
    Array<Book *> sortBooksByBorrowCount(bool reverse = false);

    bool updateBook(Book &b);
    Array<Book *> listAllBooks();

    // Patron operations
    bool addPatron(Patron &p);
    bool removePatronById(string patronID);
    bool removePatronByName(string patronName);
    Patron *findPatronById(string patronID);
    Patron *findPatronByName(string patronName);
    Array<Patron *> findPatronsById(string patronID);
    Array<Patron *> findPatronsByName(string patronName);
    Array<Patron *> sortPatronsByName(bool reverse = false);
    Array<Patron *> sortPatronsByMembershipDate(bool reverse = false);
    Array<Patron *> sortPatronsByBorrowCount(bool reverse = false);
    bool updatePatron(Patron &p);
    Array<Patron *> listAllPatrons();

    // Transaction operations
    bool addTransaction(Transaction &t);
    Transaction *findTransactionById(string txID);
    Array<Transaction *> listAllTransactions();
    Array<Transaction *> listTransactionsForPatron(string patronID);
    Array<Transaction *> listOverdueForPatron(string patronID);
    Array<Transaction *> listTransactionsForBook(string bookID);
    Array<Transaction *> sortTransactionsByReturnDate(bool reverse = false);
    Array<Transaction *> sortTransactionsByDueDate(bool reverse = false);
    Array<Transaction *> sortTransactionsByBorrowDate(bool reverse = false);

    // Borrow/Return operations
    bool borrowBook(string patronID, string isbn);
    bool returnBook(string patronID, string isbn);
};
