#pragma once
#include <vector>
#include <string>
#include <iostream>
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
    DataStore<string, Book> bookStore;
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
