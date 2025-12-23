#include "core/LoanService.hpp"
#include <iomanip>

bool LoanService::borrowBook(const string& patronID, const string& isbn) {
    Book* book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book || !book->isAvailable()) return false;
    Patron* patron = patronManager.findPatron(PatronSearchKey::ID, patronID);
    if (!patron) return false;
    // Enforce maximum active loans per patron
    const int MAX_ACTIVE_LOANS = 5;
    if (patron->getBorrowCount() >= MAX_ACTIVE_LOANS) {
        cout << "Patron has reached maximum active loans (" << MAX_ACTIVE_LOANS << ")\n";
        return false;
    }

    // Block patrons with any outstanding overdue transactions
    Array<Transaction *> patronTx = transactionManager.findTransactions(TransactionSearchKey::PATRON_ID, patronID);
    for (auto *tptr : patronTx) {
        if (tptr && tptr->isOverdue()) {
            cout << "Patron has overdue items; cannot borrow until resolved.\n";
            return false;
        }
    }

    string transactionID = generateId("TXN");
    string borrowDate = getCurrentDate();
    string dueDate = addDays(borrowDate, 14); // 14-day loan period
    Transaction t(transactionID, isbn, patronID, borrowDate, dueDate, "", false);
    if (!transactionManager.addTransaction(t)) {
      return false;
    }
    book->incrementBorrowCount();
    patron->incrementBorrowCount();
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
    // compute fine if any and notify
    double fine = trans->calculateFine();
    if (fine > 0.0) {
        cout << "Return processed. Overdue fine: $" << fixed << setprecision(2) << fine << "\n";
    }
    // persist transaction changes
    transactionManager.saveTransactions();
    book->setAvailable(true);
    patron->setBorrowCount(patron->getBorrowCount() - 1);
    return true;
}