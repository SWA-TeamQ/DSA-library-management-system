#include "core/LibraryController.hpp"
#include <iostream>

using namespace std;

// Book operations
bool LibraryController::addBook(const Book &b) { 
    booksManager.addBook(b); 
    return true; 
}

bool LibraryController::removeBook(const string &isbn) { 
    return booksManager.removeBook(BookSearchKey::ID, isbn); 
}

Book *LibraryController::findBook(const string &isbn) const { 
    return booksManager.findBook(BookSearchKey::ID, isbn); 
}

vector<Book *> LibraryController::findBooksByTitle(const string &title) const { 
    return booksManager.findBooks(BookSearchKey::TITLE, title); 
}

void LibraryController::sortBooksByTitle(bool reverse) { booksManager.sortBooksByTitle(reverse); }

void LibraryController::sortBooksByYear(bool reverse) { booksManager.sortBooksByYear(reverse); }

Book *LibraryController::updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount) { return booksManager.updateBookDetails(isbn, title, author, edition, publicationYear, category, available, borrowCount); }

void LibraryController::listAllBooks() const { booksManager.listAllBooks(); }

void LibraryController::listAllPatrons() const { patronsManager.displayAll(); }

void LibraryController::sortPatrons(PatronSortKey key, bool reverse) { 
    patronsManager.sortPatrons(key, reverse); 
}

bool LibraryController::updatePatron(const Patron &p) { 
    return patronsManager.updatePatron(p); 
}

// Transaction operations

bool LibraryController::addTransaction(const Transaction &t) { 
    return transactionsManager.addTransaction(t); 
}




// Borrow/Return operations
bool LibraryController::borrowBook(const string &patronID, const string &isbn) {
    return loanService->borrowBook(patronID, isbn);
}

bool LibraryController::returnBook(const string &patronID, const string &isbn) {
    return loanService->returnBook(patronID, isbn);
}
