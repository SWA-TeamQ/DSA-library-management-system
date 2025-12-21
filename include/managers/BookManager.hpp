#pragma once
#include <vector>
#include <string>
#include "models/Book.hpp"
#include "dsa/HashTable.hpp"
#include "dsa/MergeSort.hpp"
#include "core/DataStore.hpp"
#include "BookSearch.hpp"

using namespace std;

class BookManager
{
private:
    HashTable<Book> books;
    BookSearchMap searchMap;
    DataStore<Book> bookStore{"books.txt"};
    vector<Book> bookList;

public:
    BookManager(const string &filename) : bookStore(filename)
    {
        loadBooks();
    }

    // Data operations
    void loadBooks();
    void saveBooks();

    // Book operations
    bool addBook(const Book &b);
    bool updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount);
    bool removeBookByISBN(const string &isbn);
    
    // searching
    Book *findBookByISBN(const string &isbn) const;
    vector<Book *> findBooksByTitle(const string &title) const;
    vector<Book *> findBooksByAuthor(const string &author) const;
    
    // sorting
    void sortBooksByTitle(bool reverse = false);
    void sortBooksByYear(bool reverse = false);
    
    // listing
    void listAllBooks() const;
    
    void buildSearchIndex();
};
