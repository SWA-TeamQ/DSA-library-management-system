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
    DataStore<Book> bookStore;
    vector<Book> bookList;

public:
    BookManager(const string &filename)
    {
        bookStore = DataStore<Book>(filename);
        loadBooks();
    }

    // Data operations
    void loadBooks(){
        bookStore.load();
    };
    void saveBooks(){
        bookStore.save();
    };

    // Book operations
    bool addBook(const Book &b){
        books.insert(b);
        searchMap.insert(b);
        bookList.push_back(b);
        return true;
    };
    bool updateBookDetails(BookAllKey key);
    bool removeBook(BookSearchKey key);
    
    // searching
    Book *findBook(BookSearchKey key) const;
    vector<Book *> findBooks(BookSearchKey key) const;
    
    // sorting
    void sortBooks(BooksSortKey key, bool reverse = false);
    
    // listing
    void listAllBooks() const;
    
    void buildSearchIndex();
};
