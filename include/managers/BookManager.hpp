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
    HashTable<string, Book> bookTable; // id -> book
    BookSearchMap searchMap;

public:
    BookManager(const string &filename) : bookStore(filename)
    {
        loadBooks();
    }

    // Data operations
    void loadBooks(){
        bookTable.clear();
        searchMap.clear();

        if(!bookStore.loadData(bookTable)){
            cout << "Warning: unable to load books from file" << endl;
        }
        buildSearchMap();
    }

    void saveBooks(){
        bookStore.saveData(bookTable);
    }
    
    // title -> id, author -> id
    void buildSearchMap(){
        searchMap.buildIndices(bookTable);
    } 

    // Book operations
    bool addBook(const Book &b);
    bool updateBook(const Book &b);
    bool removeBook(const BookSearchKey key, const string &value);
    Book *findBook(const BookSearchKey key, const string &value) const;
    Array<Book *> findBooks(const BookSearchKey key, const string &value) const;
    Array<Book *> sortBooks(const BookSortKey key, bool reverse = false);
    Array<Book *> getAllBooks() const;
};
