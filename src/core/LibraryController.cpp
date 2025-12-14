#include "core/LibraryController.hpp"
#include <iostream>
#include <ctime>
using namespace std;

bool LibraryController::addBook(const Book &b) { return booksManager.addBook(b); }

bool LibraryController::removeBookByISBN(const string &isbn) { return booksManager.removeBookByISBN(isbn); }

Book *LibraryController::findBookByISBN(const string &isbn) { return booksManager.findBookByISBN(isbn); }

vector<Book *> LibraryController::findBooksByTitle(const string &title) const { return booksManager.findBooksByTitle(title); }

vector<Book *> LibraryController::findBooksByAuthor(const string &author) const { return booksManager.findBooksByAuthor(author); }

void LibraryController::sortBooksByTitle(bool reverse) { booksManager.sortBooksByTitle(reverse); }

void LibraryController::sortBooksByYear(bool reverse) { booksManager.sortBooksByYear(reverse); }

Book *LibraryController::updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount) { return booksManager.updateBookDetails(isbn, title, author, edition, publicationYear, category, available, borrowCount); }

void LibraryController::listAllBooks() const { booksManager.listAllBooks(); }

void LibraryController::listAllPatrons() const { patronsManager.displayAll(); }

void LibraryController::listAllTransactions() const { transactionsManager.displayAll(); }

bool LibraryController::addPatron(const Patron &p) { return patronsManager.addPatron(p); }

Patron* LibraryController::findPatronByID(const string &id) { return patronsManager.findPatron(id); }

bool LibraryController::borrowBook(const string &patronID, const string &isbn)
{
    Book* book = findBookByISBN(isbn);
    if (!book || !book->isAvailable()) return false;
    Patron* patron = findPatronByID(patronID);
    if (!patron) return false;
    string transactionID = "T" + to_string(time(nullptr));
    Transaction t(transactionID, isbn, patronID, "2023-01-01", "2023-01-15", "", false);
    if (!transactionsManager.addTransaction(t)) return false;
    book->setAvailable(false);
    book->incrementBorrowCount();
    patron->setBorrowCount(patron->getBorrowCount() + 1);
    return true;
}

bool LibraryController::returnBook(const string &patronID, const string &isbn)
{
    Book* book = findBookByISBN(isbn);
    if (!book || book->isAvailable()) return false;
    Patron* patron = findPatronByID(patronID);
    if (!patron) return false;
    // find transaction
    Transaction* trans = nullptr;
    for (auto* t : transactionsManager.getAllTransactions()) {
        if (t->getBookID() == isbn && t->getPatronID() == patronID && !t->isReturned()) {
            trans = t;
            break;
        }
    }
    if (!trans) return false;
    trans->setReturnDate("2023-01-10");
    trans->setReturned(true);
    book->setAvailable(true);
    patron->setBorrowCount(patron->getBorrowCount() - 1);
    return true;
}


