#include <iostream>
#include "managers/BookManager.hpp"
#include "dsa/MergeSort.hpp"

using namespace std;

bool BookManager::addBook(const Book &book)
{
    bookTable[book.getKey()] = book;
    searchMap.insert(book);
    bookStore.addData(book); // persist after addition
    return true;
}

bool BookManager::removeBook(const BookSearchKey key, const string &value)
{
    vector<string> ids;
    switch (key)
    {
    case BookSearchKey::ID:
        ids.push_back(value);
        break;
    case BookSearchKey::TITLE:
        ids = searchMap.findByTitle(value);
        break;
    case BookSearchKey::AUTHOR:
        ids = searchMap.findByAuthor(value);
        break;
    case BookSearchKey::CATEGORY:
        ids = searchMap.findByCategory(value);
        break;
    }

    if (ids.empty())
    {
        return false;
    }

    bool deleted = false;
    for (const auto &id : ids)
    {
        Book *b = bookTable.find(id);
        if (!b)
            continue;
        if (!b->isAvailable())
        {
            cout << "Book " << b->getKey() << " is already borrowed so it couldn't be removed" << endl;
            continue;
        }
        deleted = true;
        searchMap.remove(*b);
        bookTable.remove(id);
    }

    if (deleted)
    {
        saveBooks();
    }
    return deleted;
}

// Search a Book by its searchable keys
Book *BookManager::findBook(const BookSearchKey key, const string &value) const
{
    vector<string> ids;
    switch (key)
    {
    case BookSearchKey::ID:
        ids.push_back(value);
        break;
    case BookSearchKey::TITLE:
        ids = searchMap.findByTitle(value);
        break;
    case BookSearchKey::AUTHOR:
        ids = searchMap.findByAuthor(value);
        break;
    case BookSearchKey::CATEGORY:
        ids = searchMap.findByCategory(value);
        break;
    }

    if (ids.empty())
    {
        return nullptr;
    }

    Book *book = bookTable.find(ids[0]);
    if (book)
    {
        return book;
    }
    return nullptr;
}

// Search Books by a specific key
vector<Book *> BookManager::findBooks(const BookSearchKey key, const string &value) const
{
    vector<string> ids;
    switch (key)
    {
    case BookSearchKey::ID:
        ids.push_back(value);
        break;
    case BookSearchKey::CATEGORY:
        ids = searchMap.findByCategory(value);
        break;
    case BookSearchKey::TITLE:
        ids = searchMap.findByTitle(value);
        break;
    case BookSearchKey::AUTHOR:
        ids = searchMap.findByAuthor(value);
        break;
    }

    vector<Book *> books;
    for (const auto &id : ids)
    {
        Book *book = bookTable.find(id);
        if (book)
        {
            books.push_back(book);
        }
    }
    return books;
}

// Update a book details
bool BookManager::updateBook(const Book &newBook)
{
    Book *oldBook = bookTable.find(newBook.getKey());
    if (oldBook == nullptr)
    {
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

vector<Book *> BookManager::sortBooks(const BookSortKey key, bool reverse)
{
    vector<Book *> sortedBooks = bookTable.all();

    switch (key)
    {
    case BookSortKey::TITLE:
        mergeSort(sortedBooks, [](const Book *b)
                  { return b->getTitle(); }, reverse);
        break;
    case BookSortKey::AUTHOR:
        mergeSort(sortedBooks, [](const Book *b)
                  { return b->getAuthor(); }, reverse);
        break;
    case BookSortKey::YEAR:
        mergeSort(sortedBooks, [](const Book *b)
                  { return b->getPublicationYear(); }, reverse);
        break;
    case BookSortKey::BORROW_COUNT:
        mergeSort(sortedBooks, [](const Book *b)
                  { return b->getBorrowCount(); }, reverse);
        break;
    }
    return sortedBooks;
}

vector<Book *> BookManager::getAllBooks() const
{
    return bookTable.all();
}