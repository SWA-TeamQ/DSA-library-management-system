#include "core/LoanService.hpp"
#include <iomanip>
#include <algorithm>

const int LOAN_DAYS = 15;

bool LoanService::borrowBook(string patronID, string isbn)
{
    Book *book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book)
    {
        cout << "Book not found.\n";
        return false;
    }

    // Ensure at least one copy is available
    if (book->getCurrentQuantity() <= 0)
    {
        cout << "No copies available for book " << isbn << "\n";
        return false;
    }

    Patron *patron = patronManager.findPatron(PatronSearchKey::ID, patronID);
    if (!patron)
    {
        cout << "Patron not found.\n";
        return false;
    }

    // Maximum active loans per patron
    const int MAX_ACTIVE_LOANS = 5;
    if (patron->getActiveBorrowCount() >= MAX_ACTIVE_LOANS)
    {
        cout << "Patron has reached maximum active loans ("
             << MAX_ACTIVE_LOANS << ")\n";
        return false;
    }

    // Block patrons with overdue transactions
    Array<Transaction *> patronTx =
        transactionManager.findTransactions(TransactionSearchKey::PATRON_ID, patronID);

    for (auto *t : patronTx)
    {
        if (t && t->isOverdue())
        {
            cout << "Patron has overdue items; cannot borrow until resolved.\n";
            return false;
        }
    }

    book->decrementCurrentQuantity();
    book->incrementBorrowCount();         // lifetime (never decreases)
    patron->incrementActiveBorrowCount(); // active
    patron->incrementBorrowCount();       // lifetime

    // create transaction
    string transactionID = generateId("TXN");
    string borrowDate = getCurrentDate();
    string dueDate = addDays(borrowDate, LOAN_DAYS);

    Transaction t(transactionID, isbn, patronID, borrowDate, dueDate);

    if (!transactionManager.addTransaction(t))
    {
        book->incrementCurrentQuantity();
        patron->decrementActiveBorrowCount();
        return false;
    }

    bookManager.saveBooks();
    return true;
}

bool LoanService::returnBook(string patronID, string isbn)
{
    Book *book = bookManager.findBook(BookSearchKey::ID, isbn);
    if (!book)
    {
        cout << "Book not found.\n";
        return false;
    }

    Patron *patron = patronManager.findPatron(PatronSearchKey::ID, patronID);
    if (!patron)
    {
        cout << "Patron not found.\n";
        return false;
    }

    Transaction *trans = nullptr;
    for (auto *t : transactionManager.getAllTransactions())
    {
        if (t->getBookID() == isbn &&
            t->getPatronID() == patronID &&
            !t->isReturned())
        {
            trans = t;
            break;
        }
    }

    if (!trans)
    {
        cout << "Active transaction not found.\n";
        return false;
    }

    trans->setReturnDate(getCurrentDate());
    trans->setReturned(true);

    // Compute fine if any
    double fine = trans->calculateFine();
    if (fine > 0.0)
    {
        cout << "Return processed. Overdue fine: $"
             << fixed << setprecision(2) << fine << "\n";
    }

    // Persist transaction changes
    transactionManager.saveTransactions();

    // Restore book copy (multi-copy safe)
    if (book->getCurrentQuantity() < book->getTotalQuantity())
    {
        book->incrementCurrentQuantity();
    }
    bookManager.saveBooks();

    // Decrement active borrow count
    patron->decrementActiveBorrowCount();
    return true;
}
