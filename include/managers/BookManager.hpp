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
    vector<Book> bookList;
    HashTable<string, int> books;
    BookSearchMap searchMap;
    DataStore<Book> bookStore;

public:
    BookManager(const string &filename)
    {
        bookStore = DataStore<Book>(filename);
        loadBooks();
        buildSearchIndex();
        buildSearchMap();
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
        int index = bookList.size() - 1;
        books.insert(b.getISBN(), index);
        searchMap.addBook(b);
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
    void buildSearchMap();
};
