#include "LibraryController.hpp"
#include <iostream>

using namespace std;

void LibraryController::loadBooks()
{
    vector<Book> bookList;
    bookStore.loadData(bookList); // load from books.txt
    for (auto &b : bookList)
        books.insert(b); // insert into hash table
}

void LibraryController::saveBooks()
{
    vector<Book *> allBooks = books.all();
    vector<Book> bookList;
    for (auto *b : allBooks)
        bookList.push_back(*b);
    bookStore.saveData(bookList); // save to books.txt
}

bool LibraryController::addBook(const Book &b) {
    if (books.insert(b)) {
        saveBooks();  // persist after addition
        return true;
    }
    return false;
}

bool LibraryController::removeBookByISBN(const string &isbn) {
    if (books.erase(isbn)) {
        saveBooks();  // persist after removal
        return true;
    }
    return false;
}

Book* LibraryController::findBookByISBN(const string &isbn) {
    return books.find(isbn);
}

vector<Book*> LibraryController::findBooksByTitle(const string &title) { 
    vector<Book*> matches;
    for (auto *b : books.all()) {
        if (b->getTitle() == title) {
            matches.push_back(b);
        }
    }
    return matches;
}

vector<Book*> LibraryController::findBooksByAuthor(const string &author) {
 vector<Book*> matches;
    for (auto *b : books.all()) {
        if (b->getAuthor() == author) {
            matches.push_back(b);
        }
    }
    return matches;
}

Book* LibraryController::updateBookDetails(
    const string& isbn,
    const string& title,
    const string& author,
    const string& edition,
    const string& publicationYear,
    const string& category,
    bool available,
    int borrowCount
) {
    Book* b = findBookByISBN(isbn);
    if (!b) return nullptr;

    bool changed = false;

    if (!title.empty())      { b->setTitle(title); changed = true; }
    if (!author.empty())     { b->setAuthor(author); changed = true; }
    if (!edition.empty())    { b->setEdition(edition); changed = true; }
    if (!publicationYear.empty()) {
        b->setPublicationYear(publicationYear);
        changed = true;
    }
    if (!category.empty())   { b->setCategory(category); changed = true; }

    if (b->isAvailable() != available) {
        b->setAvailable(available);
        changed = true;
    }
    if (b->getBorrowCount() != borrowCount) {
        b->setBorrowCount(borrowCount);
        changed = true;
    }

    if (changed) saveBooks();
    return b;
}   


bool LibraryController::addPatron(const Patron &p)
{
    // prevent duplicate patron IDs
    if (findPatronByID(p.getID()))
        return false;
    patrons.push_back(p);
    return true;
}

Patron *LibraryController::findPatronByID(const string &id)
{
    for (auto &p : patrons)
        if (p.getID() == id)
            return &p;
    return nullptr;
}

void LibraryController::createTransaction(const string &patronID, const string &isbn)
{
    string txID = patronID + ":" + isbn + ":" + to_string(transactions.size() + 1);
    transactions.emplace_back(txID, isbn, patronID);
}

void LibraryController::markLatestReturned(const string &patronID, const string &isbn)
{
    for (auto it = transactions.rbegin(); it != transactions.rend(); ++it)
        if (it->getBookID() == isbn && it->getPatronID() == patronID && !it->isReturned())
        {
            it->markReturned();
            break;
        }
}

bool LibraryController::borrowBook(const string &patronID, const string &isbn)
{
    auto *patron = findPatronByID(patronID);
    auto *book = findBookByISBN(isbn);
    if (!patron || !book || !book->isAvailable())
        return false;
    book->setAvailable(false);
    book->incrementBorrowCount();
    createTransaction(patronID, isbn);
    return true;
}

bool LibraryController::returnBook(const string &patronID, const string &isbn)
{
    auto *book = findBookByISBN(isbn);
    if (!book || book->isAvailable())
        return false;
    book->setAvailable(true);
    markLatestReturned(patronID, isbn);
    return true;
}

void LibraryController::listAllBooks() const
{
    cout << "--- Books ---\n";
    for (auto *b : books.all())
        b->displayDetails(cout);
}

void LibraryController::listAllPatrons() const
{
    cout << "--- Patrons ---\n";
    for (const auto &p : patrons)
        p.displayProfile();
}
