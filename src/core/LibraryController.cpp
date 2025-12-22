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

Array<Book *> LibraryController::findBooksByTitle(const string &title) const { 
    return booksManager.findBooks(BookSearchKey::TITLE, title); 
}

Array<Book *> LibraryController::findBooksByAuthor(const string &author) const {
    return booksManager.findBooks(BookSearchKey::AUTHOR, author);
}

Array<Book *> LibraryController::sortBooks(BookSortKey key, bool reverse) { 
    return booksManager.sortBooks(key, reverse); 
}

bool LibraryController::updateBook(const Book &b) { 
    return booksManager.updateBook(b); 
}

void LibraryController::listAllBooks() const { 
    for (auto *b : booksManager.sortBooks(BookSortKey::TITLE)) {
        cout << b->getTitle() << " | " << b->getAuthor() << " | " << b->getISBN() << "\n";
    }
}

bool LibraryController::removePatron(const string &patronID) {
    return patronsManager.removePatron(PatronSearchKey::ID, patronID);
}

Patron *LibraryController::findPatron(const string &patronID) const {
    return patronsManager.findPatron(PatronSearchKey::ID, patronID);
}

void LibraryController::listAllPatrons() const { patronsManager.displayAll(); }

Array<Patron *> LibraryController::sortPatrons(PatronSortKey key, bool reverse) { 
    return patronsManager.sortPatrons(key, reverse); 
}

bool LibraryController::updatePatron(const Patron &p) { 
    return patronsManager.updatePatron(p); 
}

// Transaction operations

bool LibraryController::addTransaction(const Transaction &t) { 
    return transactionsManager.addTransaction(t); 
}

void LibraryController::listAllTransactions() const {
    for (auto *t : transactionsManager.getAllTransactions()) {
        cout << t->getID() << " | " << t->getBookID() << " | " << t->getPatronID() << " | returned:" << (t->isReturned() ? "yes" : "no") << "\n";
    }
}




// Borrow/Return operations
bool LibraryController::borrowBook(const string &patronID, const string &isbn) {
    return loanService.borrowBook(patronID, isbn);
}

bool LibraryController::returnBook(const string &patronID, const string &isbn) {
    return loanService.returnBook(patronID, isbn);
}
