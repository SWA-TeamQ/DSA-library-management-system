#include "core/LibraryController.hpp"
#include <iostream>
using namespace std;

void LibraryController::loadBooks() { booksManager.loadBooks(); }

void LibraryController::saveBooks() { booksManager.saveBooks(); }

bool LibraryController::addBook(const Book &b) { return booksManager.addBook(b); }

bool LibraryController::removeBookByISBN(const string &isbn) { return booksManager.removeBookByISBN(isbn); }

Book *LibraryController::findBookByISBN(const string &isbn) { return booksManager.findBookByISBN(isbn); }

vector<Book *> LibraryController::findBooksByTitle(const string &title) const { return booksManager.findBooksByTitle(title); }

vector<Book *> LibraryController::findBooksByAuthor(const string &author) const { return booksManager.findBooksByAuthor(author); }

void LibraryController::sortBooksByTitleAsc() { booksManager.sortBooksByTitleAsc(); }

void LibraryController::sortBooksByTitleDesc() { booksManager.sortBooksByTitleDesc(); }

void LibraryController::sortBooksByYearAsc() { booksManager.sortBooksByYearAsc(); }

void LibraryController::sortBooksByYearDesc() { booksManager.sortBooksByYearDesc(); }

Book *LibraryController::updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount)
{ return booksManager.updateBookDetails(isbn, title, author, edition, publicationYear, category, available, borrowCount); }

void LibraryController::listAllBooks() const { booksManager.listAllBooks(); }


// bool LibraryController::addPatron(const Patron &p)
// {
//     // prevent duplicate patron IDs
//     if (findPatronByID(p.getID()))
//         return false;
//     patrons.push_back(p);
//     return true;
// }

// Patron *LibraryController::findPatronByID(const string &id)
// {
//     for (auto &p : patrons)
//         if (p.getID() == id)
//             return &p;
//     return nullptr;
// }

// void LibraryController::createTransaction(const string &patronID, const string &isbn)
// {
//     string txID = patronID + ":" + isbn + ":" + to_string(transactions.size() + 1);
//     transactions.emplace_back(txID, isbn, patronID);
// }

// void LibraryController::markLatestReturned(const string &patronID, const string &isbn)
// {
//     for (auto it = transactions.rbegin(); it != transactions.rend(); ++it)
//         if (it->getBookID() == isbn && it->getPatronID() == patronID && !it->isReturned())
//         {
//             it->markReturned();
//             break;
//         }
// }

// bool LibraryController::borrowBook(const string &patronID, const string &isbn)
// {
//     auto *patron = findPatronByID(patronID);
//     auto *book = findBookByISBN(isbn);
//     if (!patron || !book || !book->isAvailable())
//         return false;
//     book->setAvailable(false);
//     book->incrementBorrowCount();
//     createTransaction(patronID, isbn);
//     return true;
// }

// bool LibraryController::returnBook(const string &patronID, const string &isbn)
// {
//     auto *book = findBookByISBN(isbn);
//     if (!book || book->isAvailable())
//         return false;
//     book->setAvailable(true);
//     markLatestReturned(patronID, isbn);
//     return true;
// }



// void LibraryController::listAllPatrons() const
// {
//     cout << "--- Patrons ---\n";
//     for (const auto &p : patrons)
//         p.displayDetails();
// }
