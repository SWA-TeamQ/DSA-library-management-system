#include <iostream>
#include "managers/BookManager.hpp"

using namespace std;

void BookManager::addBook(const Book& b){
    const int index = bookList.size();
    bookList.push_back(b);
    bookTable.insert(b.getKey(), index);
    searchMap.insert(b);
    bookStore.addData(b); // persist after addition
}

bool BookManager::removeBook(const BookSearchKey &key, const string &value)
{
    vector<string> ids;
    switch(key){
        case BookSearchKey::ID:
            ids.push_back(value);
            break;
        case BookSearchKey::Title:
            ids = searchMap.findByTitle(value);
            break;
        case BookSearchKey::Author:
            ids = searchMap.findByAuthor(value);
            break;
        case BookSearchKey::CATEGORY:
            ids = searchMap.findByCategory(value);
            break;
    }

    for(const auto &id : ids){
        Book *b = bookTable.find(id);
        if(!b){
            cout << "Book not found" << endl;
            return false;
        }
        if(!b->isAvailable()){
            cout << "Book is already borrowed so it couldn't be removed" << endl;
            return false;
        }
        bookList.erase(bookList.begin() + bookTable.find(id));
        bookTable.remove(id);
        searchMap.remove(*b);
    }

    saveBooks(); // persist after removal
    buildSearchIndex();
    return true;
}

// Search a Book by its searchable keys
Book *BookManager::findBook(const BookSearchKey &key, const string &value) const
{
    vector<string> isbns;
    switch(key){
        case BookSearchKey::ID:
            isbns.push_back(value);
            break;
        case BookSearchKey::CATEGORY:
            isbns = searchMap.findByCategory(value);
            break;
        case BookSearchKey::Title:
            isbns = searchMap.findByTitle(value);
            break;
        case BookSearchKey::Author:
            isbns = searchMap.findByAuthor(value);
            break;
    }

    if(isbns.empty()){
        return nullptr;
    }

    const int index = bookTable.find(isbns[0]); // only cares about the first found element
    return &bookList[index];
}

// Search Books by a specific key
vector<Book *> BookManager::findBooks(const BookSearchKey &key, const string &value)
{
    vector<string> isbns;
    switch(key){
        case BookSearchKey::ID:
            isbns.push_back(value);
            break;
        case BookSearchKey::CATEGORY:
            isbns = searchMap.findByCategory(value);
            break;
        case BookSearchKey::Title:
            isbns = searchMap.findByTitle(value);
            break;
        case BookSearchKey::Author:
            isbns = searchMap.findByAuthor(value);
            break;
    }
    vector<Book *> books;
    for(auto isbn : isbns){
        const int index = bookTable.find(isbn);
        books.push_back(&bookList[index]);
    }
    return books;
}


// Update a book details
bool BookManager::updateBook(const Book &newBook)
{
    int *indexPtr = bookTable.find(newBook.getKey());
    Book *oldBook = &bookList[*indexPtr];
    if(oldBook == nullptr){
        return false;
    }

    bool changed = false;

    if (newBook.getTitle() != oldBook->getTitle() || 
        newBook.getAuthor() != oldBook->getAuthor() ||
        newBook.getEdition() != oldBook->getEdition() ||
        newBook.getPublicationYear() != oldBook->getPublicationYear() ||
        newBook.getCategory() != oldBook->getCategory())
    {
        searchMap.remove(*oldBook);
        oldBook->setTitle(newBook.getTitle());
        oldBook->setAuthor(newBook.getAuthor());
        oldBook->setEdition(newBook.getEdition());
        oldBook->setPublicationYear(newBook.getPublicationYear());
        oldBook->setCategory(newBook.getCategory());
        searchMap.insert(*oldBook);
        changed = true;
    }

    if (changed)
    {
        saveBooks(); // persist after update
    }

    return changed;
}


void BookManager::sortBooks(const BookSortKey &key, const bool &reverse){
    switch(key){
        case BookSortKey::TITLE:
            mergeSort(bookList, [](const Book& b){
                return b.getTitle();
            }, reverse);
            break;
        case BookSortKey::AUTHOR:
            mergeSort(bookList, [](const Book& b){
                return b.getAuthor();
            }, reverse);
            break;
        case BookSortKey::YEAR:
            mergeSort(bookList, [](const Book& b){
                return b.getPublicationYear();
            }, reverse);
            break;
        case BookSortKey::BORROW_COUNT:
            mergeSort(bookList, [](const Book& b){
                return b.getBorrowCount();
            }, reverse);
            break;
    }
    saveBooks();
}