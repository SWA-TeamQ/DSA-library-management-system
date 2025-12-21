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

bool LibraryController::updateBook(const Book& b) { 
    return booksManager.updateBook(b); 
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
