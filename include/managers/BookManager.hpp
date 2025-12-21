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
    HashTable<string, int> bookTable;
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
        bookList.clear();
        bookTable.clear();
        searchMap.clear();

       if(!bookStore.loadData(bookList)){
            cout << "Warning: unable "
       };
        buildSearchIndex();
        buildSearchMap();
    };

    void saveBooks(){
        bookStore.saveData(bookList);
    };
    
    // id -> index
    void buildSearchIndex(){
        bookTable.clear();
        for(int i = 0; i < bookList.size(); i++)
            bookTable.insert(bookList[i].getKey(), i);
    };
    
    // title -> id, author -> id
    void buildSearchMap(){
        searchMap.buildIndices(bookList);
    }; 

    // Book operations
    bool addBook(const Book &b);
    bool updateBook(Book &b);
    bool removeBook(const BookSearchKey key, const string &value);
    Book *findBook(const BookSearchKey key, const string &value) const;
    vector<Book *> findBooks(const BookSearchKey key, const string &value) const;
    void sortBooks(const BooksSortKey key, bool reverse = false);
};
