#include "core/LoanService.hpp"
#include <ctime>
#include <string>
#include "models/Transaction.hpp"

bool LoanService::borrowBook(const std::string& patronID, const std::string& isbn) {
    Book* book = bookManager.findBookByISBN(isbn);
    if (!book || !book->isAvailable()) return false;
    Patron* patron = patronManager.findPatron(patronID);
    if (!patron) return false;
    std::string transactionID = "T" + std::to_string(std::time(nullptr));
    std::string borrowDate = getCurrentDate();
    std::string dueDate = "2023-01-15"; // TODO: calculate proper due date
    Transaction t(transactionID, isbn, patronID, borrowDate, dueDate, "", false);
    if (!transactionManager.addTransaction(t)) return false;
    book->setAvailable(false);
    book->incrementBorrowCount();
    patron->setBorrowCount(patron->getBorrowCount() + 1);
    return true;
}

bool LoanService::returnBook(const std::string& patronID, const std::string& isbn) {
    Book* book = bookManager.findBookByISBN(isbn);
    if (!book || book->isAvailable()) return false;
    Patron* patron = patronManager.findPatron(patronID);
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