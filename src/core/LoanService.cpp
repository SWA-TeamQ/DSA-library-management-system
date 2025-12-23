#include "core/LoanService.hpp"

bool LoanService::borrowBook(const string& patronID, const string& isbn) {
    Book* book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book || !book->isAvailable()) return false;
    Patron* patron = patronManager.findPatron(PatronSearchKey::ID, patronID);
    if (!patron) return false;
    string transactionID = "T" + to_string(time(nullptr));
    string borrowDate = getCurrentDate();
    string dueDate = "2023-01-15"; // TODO: calculate proper due date
    Transaction t(transactionID, isbn, patronID, borrowDate, dueDate, "", false);
    if (!transactionManager.addTransaction(t)) return false;
    book->setAvailable(false);
    book->incrementBorrowCount();
    patron->setBorrowCount(patron->getBorrowCount() + 1);
    return true;
}

bool LoanService::returnBook(const string& patronID, const string& isbn) {
    Book* book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book || book->isAvailable()) return false;
    Patron* patron = patronManager.findPatron(PatronSearchKey::ID, patronID);
    if (!patron) return false;
    
    Transaction* trans = nullptr;
    for (auto* t : transactionManager.getAllTransactions()) {
        if (t->getBookID() == isbn && t->getPatronID() == patronID && !t->isReturned()) {
            trans = t;
            break;
        }
    }
    if (!trans) return false;
    trans->setReturnDate(getCurrentDate());
    trans->setReturned(true);
    book->setAvailable(true);
    patron->setBorrowCount(patron->getBorrowCount() - 1);
    return true;
}