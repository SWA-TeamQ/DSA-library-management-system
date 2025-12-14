#pragma once
#include <vector>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "structures/HashTable.hpp"
#include "managers/BookManager.hpp"
#include "managers/TransactionManager.hpp"
#include "managers/PatronManager.hpp"

using namespace std;

class LibraryController {
private:
    BookHashTable books;
    PatronManager patronsManager;
    BookManager booksManager;
    TransactionManager transactionsManager;

public:
    LibraryController() = default;

    void load(){
        patronsManager.loadPatrons();
        booksManager.loadBooks();
        transactionsManager.loadTransactions();
    }

    void save(){
        patronsManager.savePatrons();
        booksManager.saveBooks();
        transactionsManager.saveTransactions();
    }

    // Book operations
    bool addBook(const Book& b);
    bool removeBookByISBN(const string& isbn);
    Book* findBookByISBN(const string& isbn);
    vector<Book*> findBooksByTitle(const string& title) const;
    vector<Book*> findBooksByAuthor(const string& author) const;
    void sortBooksByTitle(bool reverse = false);
    void sortBooksByYear(bool reverse = false);
    Book* updateBookDetails(const string& isbn, const string& title, const string& author, const string& edition, const string& publicationYear, const string& category, bool available, int borrowCount);
    void listAllBooks() const;

    // Patron operations
    bool addPatron(const Patron& p);
    Patron* findPatronByID(const string& id);

    // Borrow/Return operations
    bool borrowBook(const string& patronID, const string& isbn);
    bool returnBook(const string& patronID, const string& isbn);

    // Reporting stubs
    // void listAllBooks() const;
    // void listAllPatrons() const;
};
