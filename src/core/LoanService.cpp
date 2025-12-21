#include "core/LoanService.hpp"
#include <ctime>
#include <string>
#include "models/Transaction.hpp"

bool LoanService::borrowBook(const std::string& patronID, const std::string& isbn) {
    Book* book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book || !book->isAvailable()) return false;
    
    Patron* patron = patronManager.findPatron(patronID);
    if (!patron) return false;
    if (patron->isBorrowed()) return false; // already has an active loan
    
    std::string transactionID = "T" + std::to_string(std::time(nullptr));
    std::string borrowDate = getCurrentDate();
    std::string dueDate = "2023-12-31"; // Placeholder
    
    Transaction t(transactionID, isbn, patronID, borrowDate, dueDate, "", false);
    if (!transactionManager.addTransaction(t)) return false;
    
    book->setAvailable(false);
    book->incrementBorrowCount();
    patron->setBorrowed(true);          
    patron->incrementBorrowCount();
    
    // Persist changes
    bookManager.saveBooks();
    patronManager.savePatrons();
    
    return true;
}

bool LoanService::returnBook(const std::string& patronID, const std::string& isbn) {
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
    patron->setBorrowed(false);
    
    // Persist changes
    bookManager.saveBooks();
    patronManager.savePatrons();
    transactionManager.saveTransactions();
    
    return true;
}