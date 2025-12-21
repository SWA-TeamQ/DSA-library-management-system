#include <iostream>
#include "managers/BookManager.hpp"

using namespace std;

void BookManager::loadBooks()
{
    bookList.clear();
    bookTable.clear();
    searchMap.clear();

    bookStore.loadData(bookList); // load from books file
    buildSearchIndex();
    buildSearchMap();
}

void BookManager::addBook(const Book& b){
    const int index = bookList.size();
    bookList.push_back(b);
    bookTable.insert(b.getKey(), index);
    searchMap.insert(b);
    bookStore.addData(b); // persist after addition
}

bool BookManager::removeBook(const BookSearchKey &key, const string &value)
{
    bool deleted = false;

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
    for(auto id : ids){
        Book *b = bookTable.find(id);
        if(b){
            bookTable.remove(id);
            searchMap.remove(*b);
            deleted = true;
        }
    }
    if(deleted){
        saveBooks(); // persist after removal
        buildSearchIndex();
    }
    return deleted;
}

// Search a Book by its Id
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
    const int index = bookTable.find(isbns[0]);
    return bookList[index];
}

// Update a book details
bool BookManager::updateBook(Book &b)
{
    Book *book = bookTable.find(b.getKey());
    if(book == nullptr){
        return false;
    }

    bool changed = false;
    if(b.getTitle() )

    if (b.getTitle() != book->getTitle() || 
        b.getAuthor() != book->getAuthor() ||
        b.getEdition() != book->getEdition() ||
        b.getPublicationYear() != book->getPublicationYear() ||
        b.getCategory() != book->getCategory())
    {
        searchMap.remove(*book);
        book->setTitle(b.getTitle());
        book->setAuthor(b.getAuthor());
        book->setEdition(b.getEdition());
        book->setPublicationYear(b.getPublicationYear());
        book->setCategory(b.getCategory());
        searchMap.insert(*book);
        changed = true;
    }

    if (changed)
    {
        saveBooks(); // persist after update
    }

    return changed;
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


// display all books to the console
void BookManager::listAllBooks() const
{
    cout << "--- Books ---\n";
    for (auto *b : books.all())
        b->display();
}