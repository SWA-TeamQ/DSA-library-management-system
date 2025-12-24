#include "core/LoanService.hpp"
#include <iomanip>
#include <algorithm>
const int n= 15;
bool LoanService::borrowBook(const string& patronID, const string& isbn) {
    Book* book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book) return false;
    // ensure at least one copy is available
    if (book->getCurrentQuantity() <= 0) {
        cout << "No copies available for book " << isbn << "\n";
        return false;
    }


    Patron* patron = patronManager.findPatron(PatronSearchKey::ID, patronID);
    if (!patron) return false;

    //  maximum active loans per patron
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

        // perform in-memory updates
        book->decrementCurrentQuantity();
        book->incrementBorrowCount(); // lifetime borrow counter for the book
        patron->incrementBorrowCount(); // active borrow counter for the patron


        // create and persist transaction

        string transactionID = generateId("TXN");
        string borrowDate = getCurrentDate();
        string dueDate = addDays(borrowDate,n); 
       
        Transaction t(transactionID, isbn, patronID, borrowDate, dueDate, "", false);
        if (!transactionManager.addTransaction(t)) {

                // rollback in-memory changes on failure
                book->incrementCurrentQuantity();
                patron->setBorrowCount(std::max(0, patron->getBorrowCount() - 1));
                return false;
        }

        // persist book state
        bookManager.saveBooks();
        return true;
}


bool LoanService::returnBook(const string& patronID, const string& isbn) {
    Book* book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book) return false;
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
    // restore book copy (doesn't exceed total quantity)
    if (book->getCurrentQuantity() < book->getTotalQuantity()) {
        book->incrementCurrentQuantity();
    }
    bookManager.saveBooks();


    // decrement patron active borrow count safely
    patron->setBorrowCount(std::max(0, patron->getBorrowCount() - 1));
    return true;
}