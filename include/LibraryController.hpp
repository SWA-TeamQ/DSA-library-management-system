#pragma once
#include <vector>
#include <string>
#include "Book.hpp"
#include "Patron.hpp"
#include "Transaction.hpp"
#include "HashTable.hpp"
#include "DataStore.hpp"

using namespace std;

class LibraryController {
private:
    BookHashTable books; // Hash table keyed by ISBN
    vector<Patron> patrons;
    vector<Transaction> transactions;

    DataStore<Book> bookStore{"books.txt"};            
    DataStore<Patron> patronStore{"patrons.txt"};        
    DataStore<Transaction> logStore{"logs.txt"};

    void createTransaction(const string& patronID, const string& isbn);
    void markLatestReturned(const string& patronID, const string& isbn);
public:
    LibraryController() = default;
    
    // Data persistence
    void loadBooks();       
    void saveBooks(); 

    // Book operations
    bool addBook(const Book& b);
    bool removeBookByISBN(const string& isbn);
    Book* findBookByISBN(const string& isbn);
    vector<Book*> findBooksByTitle(const string& title);
    vector<Book*> findBooksByAuthor(const string& author);
    Book* updateBookDetails(const string& isbn, const string& title, const string& author, const string& edition, const string& publicationYear, const string& category, bool available, int borrowCount);

    // Patron operations
    bool addPatron(const Patron& p);
    Patron* findPatronByID(const string& id);

    // Borrow/Return operations
    bool borrowBook(const string& patronID, const string& isbn);
    bool returnBook(const string& patronID, const string& isbn);

    // Reporting stubs
    void listAllBooks() const;
    void listAllPatrons() const;
};
