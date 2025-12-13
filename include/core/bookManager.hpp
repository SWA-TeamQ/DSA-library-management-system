#pragma once
#include <vector>
#include <string>
#include "models/Book.hpp"
#include "structures/HashTable.hpp"
#include "structures/MergeSort.hpp"
#include "DataStore.hpp"
#include "BookSearch.hpp"

using namespace std;

class bookManager {
private:
    BookHashTable books; // Hash table keyed by ISBN
    BookSearchMap searchMap;
    DataStore<Book> bookStore{"books.txt"};// DataStore
    vector<Book> bookList;

public:
    bookManager() = default;

    // Data operations
    void loadBooks();
    void saveBooks();


    // Book operations
    bool addBook(const Book &b);
    bool removeBookByISBN(const string &isbn);
    Book *findBookByISBN(const string &isbn);
    void buildSearchIndex();
    vector<Book*> findBooksByTitle(const string &title)const;
    vector<Book*> findBooksByAuthor(const string &author)const;
    void sortBooksByTitleAsc();
    void sortBooksByTitleDesc();
    void sortBooksByYearAsc();
    void sortBooksByYearDesc();
    Book* updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount);
    void listAllBooks() const;
};
