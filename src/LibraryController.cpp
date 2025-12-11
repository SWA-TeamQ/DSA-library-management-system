#include "LibraryController.hpp"
#include <iostream>
using namespace std;

bool LibraryController::addBook(const Book& b) { return books.insert(b); }

bool LibraryController::removeBookByISBN(const string& isbn) { return books.erase(isbn); }

Book* LibraryController::findBookByISBN(const string& isbn) { return books.find(isbn); }

bool LibraryController::addPatron(const Patron& p) {
    // prevent duplicate patron IDs
    if (findPatronByID(p.getID())) return false;
    patrons.push_back(p);
    return true;
}

Patron* LibraryController::findPatronByID(const string& id) {
    for (auto& p : patrons)
        if (p.getID() == id)
            return &p;
    return nullptr;
}

void LibraryController::createTransaction(const string& patronID, const string& isbn) {
    string txID = patronID + ":" + isbn + ":" + to_string(transactions.size()+1);
    transactions.emplace_back(txID, isbn, patronID);
}

void LibraryController::markLatestReturned(const string& patronID, const string& isbn) {
    for (auto it = transactions.rbegin(); it != transactions.rend(); ++it)
        if (it->getBookID() == isbn && it->getPatronID() == patronID && !it->isReturned()) { it->markReturned(); break; }
}

bool LibraryController::borrowBook(const string& patronID, const string& isbn) {
    auto* patron = findPatronByID(patronID);
    auto* book = findBookByISBN(isbn);
    if (!patron || !book || !book->isAvailable()) return false;
    book->setAvailable(false);
    book->incrementBorrowCount();
    createTransaction(patronID, isbn);
    return true;
}

bool LibraryController::returnBook(const string& patronID, const string& isbn) {
    auto* book = findBookByISBN(isbn);
    if (!book || book->isAvailable()) return false;
    book->setAvailable(true);
    markLatestReturned(patronID, isbn);
    return true;
}

void LibraryController::listAllBooks() const {
    cout << "--- Books ---\n";
    for (auto* b : books.all()) b->displayDetails();
}

void LibraryController::listAllPatrons() const {
    cout << "--- Patrons ---\n";
    for (const auto& p : patrons) p.displayProfile();
}
