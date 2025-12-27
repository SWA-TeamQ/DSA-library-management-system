#pragma once
#include <string>
#include <iostream>
#include "dsa/Array.hpp"
#include "models/Book.hpp"
#include "dsa/HashTable.hpp"
#include "dsa/MergeSort.hpp"
#include "core/DataStore.hpp"
#include "BookSearch.hpp"

using namespace std;

class BookManager
{
private:
    // file store
    DataStore<Book> bookStore;
    HashTable<Book> bookTable; // id -> book
    BookSearchMap searchMap;

public:
    BookManager(string filename) : bookStore(filename)
    {
        loadBooks();
    }

    // Data operations
    bool loadBooks()
    {
        bookTable.clear();
        searchMap.clear();

        if (!bookStore.loadData(bookTable))
        {
            return false;
        }
        buildSearchMap();
        return true;
    }

    bool saveBooks()
    {
        return bookStore.saveData(bookTable);
    }

    // title -> id, author -> id
    void buildSearchMap()
    {
        searchMap.buildIndices(bookTable);
    }

    // Book operations
    bool addBook(Book &b);
    bool updateBook(Book &b);
    bool removeBook(BookSearchKey key, string value);
    Book *findBook(BookSearchKey key, string value);
    Array<Book *> findBooks(BookSearchKey key, string value);
    Array<Book *> sortBooks(BookSortKey key, bool reverse = false);
    Array<Book *> getAllBooks();
};
