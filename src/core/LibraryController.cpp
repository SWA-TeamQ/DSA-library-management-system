#include "core/LibraryController.hpp"

/* -------------  Book operations ---------------*/
bool LibraryController::addBook(Book &b)
{
    bookManager.addBook(b);
    return true;
}

bool LibraryController::removeBookById(string isbn)
{
    return bookManager.removeBook(BookSearchKey::ID, isbn);
}

bool LibraryController::removeBookByTitle(string title)
{
    return bookManager.removeBook(BookSearchKey::TITLE, title);
}

bool LibraryController::removeBookByAuthor(string author)
{
    return bookManager.removeBook(BookSearchKey::AUTHOR, author);
}

bool LibraryController::removeBookByCategory(string category)
{
    return bookManager.removeBook(BookSearchKey::CATEGORY, category);
}

Book *LibraryController::findBookById(string isbn)
{
    return bookManager.findBook(BookSearchKey::ID, isbn);
}

Array<Book *> LibraryController::findBooksByTitle(string title)
{
    return bookManager.findBooks(BookSearchKey::TITLE, title);
}

Array<Book *> LibraryController::findBooksByAuthor(string author)
{
    return bookManager.findBooks(BookSearchKey::AUTHOR, author);
}

Array<Book *> LibraryController::findBooksByCategory(string category)
{
    return bookManager.findBooks(BookSearchKey::CATEGORY, category);
}

Array<Book *> LibraryController::sortBooksByTitle(bool reverse)
{
    return bookManager.sortBooks(BookSortKey::TITLE, reverse);
}

Array<Book *> LibraryController::sortBooksByAuthor(bool reverse)
{
    return bookManager.sortBooks(BookSortKey::AUTHOR, reverse);
}
Array<Book *> LibraryController::sortBooksByYear(bool reverse)
{
    return bookManager.sortBooks(BookSortKey::YEAR, reverse);
}

Array<Book *> LibraryController::sortBooksByBorrowCount(bool reverse)
{
    return bookManager.sortBooks(BookSortKey::BORROW_COUNT, reverse);
}

bool LibraryController::updateBook(Book &b)
{
    return bookManager.updateBook(b);
}

Array<Book *> LibraryController::listAllBooks()
{
    return bookManager.getAllBooks();
}

/**
 *
 * Patron Section
 *
 */

bool LibraryController::addPatron(Patron &p)
{
    return patronManager.addPatron(p);
}

bool LibraryController::removePatronById(string patronID)
{
    return patronManager.removePatron(PatronSearchKey::ID, patronID);
}

bool LibraryController::removePatronByName(string patronName)
{
    return patronManager.removePatron(PatronSearchKey::NAME, patronName);
}

Patron *LibraryController::findPatronById(string patronID)
{
    return patronManager.findPatron(PatronSearchKey::ID, patronID);
}

Patron *LibraryController::findPatronByName(string patronName)
{
    return patronManager.findPatron(PatronSearchKey::NAME, patronName);
}

Array<Patron *> LibraryController::findPatronsById(string patronID)
{
    return patronManager.findPatrons(PatronSearchKey::ID, patronID);
}

Array<Patron *> LibraryController::findPatronsByName(string patronName)
{
    return patronManager.findPatrons(PatronSearchKey::NAME, patronName);
}

Array<Patron *> LibraryController::sortPatronsByName(bool reverse)
{
    return patronManager.sortPatrons(PatronSortKey::NAME, reverse);
}

Array<Patron *> LibraryController::sortPatronsByMembershipDate(bool reverse)
{
    return patronManager.sortPatrons(PatronSortKey::MEMBERSHIP_DATE, reverse);
}

Array<Patron *> LibraryController::sortPatronsByBorrowCount(bool reverse)
{
    return patronManager.sortPatrons(PatronSortKey::BORROW_COUNT, reverse);
}

bool LibraryController::updatePatron(Patron &p)
{
    return patronManager.updatePatron(p);
}

Array<Patron *> LibraryController::listAllPatrons()
{
    return patronManager.getAllPatrons();
}

/**
 *
 * Transaction section
 *
 */

bool LibraryController::addTransaction(Transaction &t)
{
    return transactionManager.addTransaction(t);
}

Transaction *LibraryController::findTransactionById(string txID)
{
    return transactionManager.findTransaction(TransactionSearchKey::ID, txID);
};

Array<Transaction *> LibraryController::listAllTransactions()
{
    return transactionManager.getAllTransactions();
}

Array<Transaction *> LibraryController::listTransactionsForPatron(string patronID)
{
    return transactionManager.findTransactions(TransactionSearchKey::PATRON_ID, patronID);
}

Array<Transaction *> LibraryController::listOverdueForPatron(string patronID)
{
    Array<Transaction *> txs = transactionManager.findTransactions(TransactionSearchKey::PATRON_ID, patronID);
    Array<Transaction *> overdue;
    for (auto *t : txs)
    {
        if (t && t->isOverdue())
            overdue.append(t);
    }

    return overdue;
}

Array<Transaction *> LibraryController::listTransactionsForBook(string bookID)
{
    return transactionManager.findTransactions(TransactionSearchKey::BOOK_ID, bookID);
}

Array<Transaction *> LibraryController::sortTransactionsByReturnDate(bool reverse)
{
    return transactionManager.sortTransactions(TransactionSortKey::RETURN_DATE, reverse);
}

Array<Transaction *> LibraryController::sortTransactionsByDueDate(bool reverse)
{
    return transactionManager.sortTransactions(TransactionSortKey::DUE_DATE, reverse);
}

Array<Transaction *> LibraryController::sortTransactionsByBorrowDate(bool reverse)
{
    return transactionManager.sortTransactions(TransactionSortKey::BORROW_DATE, reverse);
}

/**
 * Borrow/Return operations
 */

bool LibraryController::borrowBook(string patronID, string isbn)
{
    return loanService.borrowBook(patronID, isbn);
}

bool LibraryController::returnBook(string patronID, string isbn)
{
    return loanService.returnBook(patronID, isbn);
}
