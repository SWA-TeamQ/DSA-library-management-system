#include "core/LibraryController.hpp"

// Book operations
bool LibraryController::addBook(const Book &b) {
    bookManager.addBook(b); 
    return true; 
}

bool LibraryController::removeBookById(const string &isbn) { 
    return bookManager.removeBook(BookSearchKey::ID, isbn); 
}

bool LibraryController::removeBookByTitle(const string &title) { 
    return bookManager.removeBook(BookSearchKey::TITLE, title); 
}

bool LibraryController::removeBookByAuthor(const string &author) { 
    return bookManager.removeBook(BookSearchKey::AUTHOR, author); 
}

bool LibraryController::removeBookByCategory(const string &category) { 
    return bookManager.removeBook(BookSearchKey::CATEGORY, category); 
}

Book *LibraryController::findBookById(const string &isbn) const { 
    return bookManager.findBook(BookSearchKey::ID, isbn); 
}

Array<Book *> LibraryController::findBooksByTitle(const string &title) const { 
    return bookManager.findBooks(BookSearchKey::TITLE, title); 
}

Array<Book *> LibraryController::findBooksByAuthor(const string &author) const {
    return bookManager.findBooks(BookSearchKey::AUTHOR, author);
}

Array<Book *> LibraryController::findBooksByCategory(const string &category) const{
    return bookManager.findBooks(BookSearchKey::CATEGORY, category);
}

Array<Book *> LibraryController::sortBooksByTitle( bool reverse) {
    return bookManager.sortBooks(BookSortKey::TITLE, reverse);
}

Array<Book *> LibraryController::sortBooksByAuthor(bool reverse) {
    return bookManager.sortBooks(BookSortKey::AUTHOR, reverse);
}
Array<Book *> LibraryController::sortBooksByYear(bool reverse){
    return bookManager.sortBooks(BookSortKey::YEAR, reverse);
}

Array<Book *> LibraryController::sortBooksByBorrowCount(bool reverse){
    return bookManager.sortBooks(BookSortKey::BORROW_COUNT,reverse);
}


bool LibraryController::updateBook(const Book &b) { 
    return bookManager.updateBook(b); 
}


Array<Book *> LibraryController::listAllBooks() const { 
    return bookManager.getAllBooks();
}

bool LibraryController::removePatron(const string &patronID) {
    return patronManager.removePatron(PatronSearchKey::ID, patronID);
}

Patron *LibraryController::findPatron(const string &patronID) const {
    return patronManager.findPatron(PatronSearchKey::ID, patronID);
}

void LibraryController::listAllPatrons() const {
    for (auto *p : patronManager.sortPatrons(PatronSortKey::NAME)) {
        cout << p->getID() << " | " << p->getName() << " | " << p->getMembershipDate() << "\n";
    }
}

Array<Patron *> LibraryController::sortPatrons(PatronSortKey key, bool reverse) { 
    return patronManager.sortPatrons(key, reverse); 
}

bool LibraryController::updatePatron(const Patron &p) { 
    return patronManager.updatePatron(p); 
}

// Transaction operations

bool LibraryController::addTransaction(const Transaction &t) { 
    return transactionManager.addTransaction(t); 
}

void LibraryController::listAllTransactions() const {
    for (auto *t : transactionManager.getAllTransactions()) {
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
