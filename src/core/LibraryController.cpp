#include "core/LibraryController.hpp"
#include <iostream>
#include <ctime>
#include "utils/utils.hpp"
using namespace std;

bool LibraryController::addBook(const Book &b) { return booksManager.addBook(b); }

bool LibraryController::removeBookByISBN(const string &isbn) { return booksManager.removeBookByISBN(isbn); }

Book *LibraryController::findBookByISBN(const string &isbn) { return booksManager.findBookByISBN(isbn); }

vector<Book *> LibraryController::findBooksByTitle(const string &title) const { return booksManager.findBooksByTitle(title); }

vector<Book *> LibraryController::findBooksByAuthor(const string &author) const { return booksManager.findBooksByAuthor(author); }

void LibraryController::sortBooksByTitle(bool reverse) { booksManager.sortBooksByTitle(reverse); }

void LibraryController::sortBooksByYear(bool reverse) { booksManager.sortBooksByYear(reverse); }

Book *LibraryController::updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const int &publicationYear, const string &category, const int &quantity, bool available, int borrowCount) { return booksManager.updateBookDetails(isbn, title, author, edition, publicationYear, category,quantity, available, borrowCount); }

void LibraryController::listAllBooks() const { booksManager.listAllBooks(); }

void LibraryController::listAllPatrons() const { patronsManager.displayAll(); }

void LibraryController::listAllTransactions() const { transactionsManager.displayAll(); }

bool LibraryController::addPatron(const Patron &p) { return patronsManager.addPatron(p); }

Patron *LibraryController::findPatronByID(const string &id) { return patronsManager.findPatron(id); }

bool LibraryController::borrowBook(const string &patronID, const string &isbn)
{
    return loanService.borrowBook(patronID, isbn);
}

bool LibraryController::returnBook(const string &patronID, const string &isbn)
{
    return loanService.returnBook(patronID, isbn);
}

