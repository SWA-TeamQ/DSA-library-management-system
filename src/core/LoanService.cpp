#include "core/LoanService.hpp"
#include <ctime>
#include <string>

bool LoanService::borrowBook(const string &patronID, const string &isbn, string &error)
{
    Book *book = bookManager.findBookByISBN(isbn);
    if (!book)
    {
        error = "Book not found.";
        return false;
    }

    Patron *patron = patronManager.findPatron(patronID);
    if (!patron)
    {
        error = "Patron not found.";
        return false;
    }

    if (patron->getBorrowCount() >= 3)
    {
        error = "Maximum borrow limit reached (3 books).";
        return false;
    }

    if (transactionManager.hasOverdueBooks(patronID))
    {
        error = "Patron has overdue books.";
        return false;
    }

    string borrowDate = getCurrentDate();
    string dueDate = addDaysToDate(borrowDate, 14);

    Transaction t("T" + to_string(time(nullptr)), isbn, patronID,
                  borrowDate, dueDate, "", false);

    if (!transactionManager.addTransaction(t))
    {
        error = "Failed to record transaction.";
        return false;
    }

    book->incrementBorrowCount();
    if (book->getBorrowCount() >= book->getQuantity())
        book->setAvailable(false);

    patron->setBorrowCount(patron->getBorrowCount() + 1);
     // Persist changes
    transactionManager.saveTransactions();
    bookManager.saveBooks();
    patronManager.savePatrons();
    return true;
}
// Overloaded function without error string
bool LoanService::borrowBook(const std::string &patronID, const std::string &isbn)
{
    std::string err;
    return borrowBook(patronID, isbn, err);
}


bool LoanService::returnBook(const string &patronID, const string &isbn, double &fine)
{
    fine = 0.0;

    for (auto *t : transactionManager.getAllTransactions())
    {
        if (t->getPatronID() == patronID &&
            t->getBookID() == isbn &&
            !t->isReturned())
        {
            t->setReturnDate(getCurrentDate());
            t->setReturned(true);

            fine = t->calculateFine();

            Book *book = bookManager.findBookByISBN(isbn);
            Patron *patron = patronManager.findPatron(patronID);

            book->decrementBorrowCount();
            if (book->getBorrowCount() < book->getQuantity())
                book->setAvailable(true);

            patron->setBorrowCount(patron->getBorrowCount() - 1);

           
              // Persist changes
            transactionManager.saveTransactions();
            bookManager.saveBooks();
            patronManager.savePatrons();
            return true;
        }
    }
    return false;
}
// Overloaded function without fine output
bool LoanService::returnBook(const std::string &patronID, const std::string &isbn)
{
    double ignored = 0.0;
    return returnBook(patronID, isbn, ignored);
}