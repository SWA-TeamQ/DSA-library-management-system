#include <iostream>
#include "managers/BookManager.hpp"
#include "dsa/MergeSort.hpp"

using namespace std;

bool BookManager::addBook(const Book &book)
{
    Book* existing = bookTable.find(book.getKey());

    if (!existing)
    {
        // New book
        Book newBook = book;
        newBook.setBorrowCount(0);
        newBook.setTotalQuantity(newBook.getTotalQuantity());
        
        bookTable[newBook.getKey()] = newBook;
        searchMap.insert(newBook);
        bookStore.addData(newBook); // persist new book
        return true;
    }
    return false;
}

bool BookManager::removeBook(const BookSearchKey key, const string &value)
{
    Array<string> ids;
    switch (key)
    {
    case BookSearchKey::ID:
        ids.append(value);
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
    Array<string> ids;
    switch (key)
    {
    case BookSearchKey::ID:
        ids.append(value);
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
Array<Book *> BookManager::findBooks(const BookSearchKey key, const string &value) const
{
    Array<string> ids;
    switch (key)
    {
    case BookSearchKey::ID:
        ids.append(value);
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

    Array<Book *> books;
    for (const auto &id : ids)
    {
        Book *book = bookTable.find(id);
        if (book)
        {
            books.append(book);
        }
    }
    return books;
}

// Update a book details
bool BookManager::updateBook(const Book& newBook)
{
    Book* oldBook = bookTable.find(newBook.getKey());
    if (!oldBook)
        return false;

    bool changed =
        newBook.getTitle() != oldBook->getTitle() ||
        newBook.getAuthor() != oldBook->getAuthor() ||
        newBook.getEdition() != oldBook->getEdition() ||
        newBook.getPublicationYear() != oldBook->getPublicationYear() ||
        newBook.getCategory() != oldBook->getCategory();
        if (!changed)
        return false;

    // Update search index (title, author, etc.)
    searchMap.remove(*oldBook);

    oldBook->setTitle(newBook.getTitle());
    oldBook->setAuthor(newBook.getAuthor());
    oldBook->setEdition(newBook.getEdition());
    oldBook->setPublicationYear(newBook.getPublicationYear());
    oldBook->setCategory(newBook.getCategory());

    searchMap.insert(*oldBook);

    saveBooks();  // persist once

    return true;
}

Array<Book *> BookManager::sortBooks(const BookSortKey key, bool reverse) const
{
    Array<Book *> sortedBooks = bookTable.all();

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

Array<Book *> BookManager::getAllBooks() const
{
    return bookTable.all();
}