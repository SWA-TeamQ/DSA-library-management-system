#include "core/LibraryController.hpp"
#include <iostream>
using namespace std;

bool LibraryController::addBook(const Book &b) { return booksManager.addBook(b); }

bool LibraryController::removeBookByISBN(const string &isbn) { return booksManager.removeBookByISBN(isbn); }

Book *LibraryController::findBookByISBN(const string &isbn) { return booksManager.findBookByISBN(isbn); }

vector<Book *> LibraryController::findBooksByTitle(const string &title) const { return booksManager.findBooksByTitle(title); }

vector<Book *> LibraryController::findBooksByAuthor(const string &author) const { return booksManager.findBooksByAuthor(author); }

void LibraryController::sortBooksByTitle(bool reverse = false) { booksManager.sortBooksByTitle(reverse); }

void LibraryController::sortBooksByYear(bool reverse = false) { booksManager.sortBooksByYear(reverse); }

void LibraryController::sortBooksByYear(bool reverse = false) { booksManager.sortBooksByYear(reverse); }

Book *LibraryController::updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount) { return booksManager.updateBookDetails(isbn, title, author, edition, publicationYear, category, available, borrowCount); }

void LibraryController::listAllBooks() const { booksManager.listAllBooks(); }


