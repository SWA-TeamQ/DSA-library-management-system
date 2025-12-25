#include "core/LoanService.hpp"

bool LoanService::borrowBook(const string &patronID, const string &isbn)
{
    Book *book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book || !book->isAvailable())
        return false;
    Patron *patron = patronManager.findPatron(PatronSearchKey::ID, patronID);
    if (!patron)
        return false;
    // Enforce maximum active loans per patron (count active transactions)
    const int MAX_ACTIVE_LOANS = 5;
    Array<Transaction *> patronTx = transactionManager.findTransactions(TransactionSearchKey::PATRON_ID, patronID);
    int activeLoans = 0;
    for (auto *tptr : patronTx)
    {
        if (tptr && !tptr->isReturned())
            activeLoans++;
    }
    if (activeLoans >= MAX_ACTIVE_LOANS)
    {
        cout << "Patron has reached maximum active loans (" << MAX_ACTIVE_LOANS << ")\n";
        return false;
    }

    // Block patrons with any outstanding overdue transactions
    for (auto *tptr : patronTx)
    {
        if (tptr && tptr->isOverdue())
        {
            cout << "Patron has overdue items; cannot borrow until resolved.\n";
            return false;
        }
    }

    string transactionID = generateId("TXN");
    string borrowDate = getCurrentDate();
    string dueDate = addDays(borrowDate, 14); // 14-day loan period
    Transaction t(transactionID, isbn, patronID, borrowDate, dueDate, "", false);
    if (!transactionManager.addTransaction(t))
    {
        return false;
    }
    // Update quantities and counts
    book->decrementCurrentQuantity();
    book->incrementBorrowCount();
    // Track patron lifetime borrows (do not use for active limit)
    patron->incrementBorrowCount();
    // Persist book/patron changes
    bookManager.saveBooks();
    patronManager.savePatrons();
    return true;
}

bool LoanService::returnBook(const string &patronID, const string &isbn)
{
    Book *book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book)
        return false;
    Patron *patron = patronManager.findPatron(PatronSearchKey::ID, patronID);
    if (!patron)
        return false;

    Transaction *trans = nullptr;
    for (auto *t : transactionManager.getAllTransactions())
    {
        if (t->getBookID() == isbn && t->getPatronID() == patronID && !t->isReturned())
        {
            trans = t;
            break;
        }
    }
    if (!trans)
        return false;
    trans->setReturnDate(getCurrentDate());
    trans->setReturned(true);
    // compute fine if any and notify
    double fine = trans->calculateFine();
    if (fine > 0.0)
    {
        cout << "Return processed. Overdue fine: $" << fixed << setprecision(2) << fine << "\n";
    }
    // persist transaction changes
    transactionManager.saveTransactions();
    // Restore book quantity and persist
    book->incrementCurrentQuantity();
    bookManager.saveBooks();
    // Update patron borrowed flag based on remaining active transactions
    Array<Transaction *> patronTx2 = transactionManager.findTransactions(TransactionSearchKey::PATRON_ID, patronID);
    bool hasActive = false;
    for (auto *tp : patronTx2)
    {
        if (tp && !tp->isReturned())
        {
            hasActive = true;
            break;
        }
    }
    patron->setBorrowed(hasActive);
    patronManager.savePatrons();
    return true;
}
