#pragma once
#include <vector>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "structures/HashTable.hpp"
#include "core/bookManager.hpp"

using namespace std;

class LibraryController {
private:
    BookHashTable books; // Hash table keyed by ISBN
    vector<Patron> patrons;
    vector<Transaction> transactions;
    bookManager booksManager; // delegate books

    void createTransaction(const string& patronID, const string& isbn);
    void markLatestReturned(const string& patronID, const string& isbn);
public:
    LibraryController() = default;

    // Data operations
    void loadBooks();
    void saveBooks();

    // Book operations
    bool addBook(const Book& b);
    bool removeBookByISBN(const string& isbn);
    Book* findBookByISBN(const string& isbn);
    vector<Book*> findBooksByTitle(const string& title) const;
    vector<Book*> findBooksByAuthor(const string& author) const;
    void sortBooksByTitleAsc();
    void sortBooksByTitleDesc();
    void sortBooksByYearAsc();
    void sortBooksByYearDesc();
    Book* updateBookDetails(const string& isbn, const string& title, const string& author, const string& edition, const string& publicationYear, const string& category, bool available, int borrowCount);
    void listAllBooks() const;

    // Patron operations
    // bool addPatron(const Patron& p);
    // Patron* findPatronByID(const string& id);

    // Borrow/Return operations
    bool borrowBook(const string& patronID, const string& isbn);
    bool returnBook(const string& patronID, const string& isbn);

    // Reporting stubs
    // void listAllBooks() const;
    // void listAllPatrons() const;
};
