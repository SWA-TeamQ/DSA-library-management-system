#pragma once
#include <vector>
#include <string>
#include "models/Book.hpp"
#include "dsa/HashTable.hpp"
#include "dsa/MergeSort.hpp"
#include "core/DataStore.hpp"
#include "BookSearch.hpp"

using BookHashTable = HashTable<Book>;

using namespace std;

class BookManager
{
private:
    BookHashTable books; // Hash table keyed by ISBN
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
    bool removeBookByISBN(const string &isbn);
    Book *findBookByISBN(const string &isbn) const;
    void buildSearchIndex();
    vector<Book *> findBooksByTitle(const string &title) const;
    vector<Book *> findBooksByAuthor(const string &author) const;
    void sortBooksByTitle(bool reverse = false);
    void sortBooksByYear(bool reverse = false);
    Book *updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount);
    void listAllBooks() const;
};
