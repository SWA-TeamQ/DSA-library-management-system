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

void LibraryController::sortBooks(BookSortKey key, bool reverse) { 
    booksManager.sortBooks(key, reverse); 
}

bool LibraryController::updateBook(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount) { 
    return booksManager.updateBook(isbn, title, author, edition, publicationYear, category, available, borrowCount); 
}

void LibraryController::listAllBooks() const { 
    booksManager.listAllBooks(); 
}

// Patron operations
bool LibraryController::addPatron(const Patron &p) { 
    return patronsManager.addPatron(p); 
}

bool LibraryController::removePatron(const string &patronID) { 
    return patronsManager.removePatron(patronID); 
}

Patron *LibraryController::findPatron(const string &patronID) const { 
    return patronsManager.findPatron(patronID); 
}

void LibraryController::sortPatrons(PatronSortKey key, bool reverse) { 
    patronsManager.sortPatrons(key, reverse); 
}

bool LibraryController::updatePatron(const string &patronID, const string &name, const string &contact, const string &membershipDate, int borrowCount) { 
    return patronsManager.updatePatron(patronID, name, contact, membershipDate, borrowCount); 
}

void LibraryController::listAllPatrons() const { 
    patronsManager.listAllPatrons(); 
}

// Transaction operations
void LibraryController::listAllTransactions() const { 
    transactionsManager.listAllTransactions(); 
}

// Borrow/Return operations
bool LibraryController::borrowBook(const string &patronID, const string &isbn) {
    return loanService->borrowBook(patronID, isbn);
}

bool LibraryController::returnBook(const string &patronID, const string &isbn) {
    return loanService->returnBook(patronID, isbn);
}
