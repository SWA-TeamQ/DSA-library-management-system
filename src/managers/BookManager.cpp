#include "managers/BookManager.hpp"

using namespace std;

bool BookManager::addBook(Book &book)
{
    Book *existing = bookTable.find(book.getKey());

    if (!existing)
    {
        // New book
        Book newBook = book;
        newBook.setBorrowCount(0);
        newBook.setTotalQuantity(book.getTotalQuantity());

        bookTable[newBook.getKey()] = newBook;
        searchMap.insert(newBook);
        bookStore.addData(newBook); // persist new book
        return true;
    }
    return false;
}

bool BookManager::removeBook(BookSearchKey key, string value)
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
    for (auto &id : ids)
    {
        Book *b = bookTable.find(id);
        if (!b)
            continue;
        // Only allow removal if all copies are returned
        if (!b->isAllReturned())
        {
            cout << "Book " << b->getKey() << " has copies currently borrowed; couldn't be removed" << endl;
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
Book *BookManager::findBook(BookSearchKey key, string value)
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
Array<Book *> BookManager::findBooks(BookSearchKey key, string value)
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
    for (auto &id : ids)
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
bool BookManager::updateBook(Book &newBook)
{
    Book *oldBook = bookTable.find(newBook.getKey());
    if (!oldBook)
        return false;

    bool changed = false;

    Array<Field> BookSchema = bookSchema();
    for (auto &field : BookSchema)
    {
        changed = newBook.getField(field.key) != oldBook->getField(field.key);
    }

    if (!changed)
        return true;

    // Update search index (title, author, etc.)
    searchMap.remove(*oldBook);

    for (auto &field : BookSchema)
    {
        oldBook->setField(field.key, newBook.getField(field.key));
    }

    searchMap.insert(*oldBook);

    return saveBooks(); // persist once
}

Array<Book *> BookManager::sortBooks(BookSortKey key, bool reverse)
{
    Array<Book *> sortedBooks = bookTable.all();

    switch (key)
    {
    case BookSortKey::TITLE:
        mergeSort(sortedBooks, [](Book *b)
                  { return b->getTitle(); }, reverse);
        break;
    case BookSortKey::AUTHOR:
        mergeSort(sortedBooks, [](Book *b)
                  { return b->getAuthor(); }, reverse);
        break;
    case BookSortKey::YEAR:
        mergeSort(sortedBooks, [](Book *b)
                  { return b->getPublicationYear(); }, reverse);
        break;
    case BookSortKey::BORROW_COUNT:
        mergeSort(sortedBooks, [](Book *b)
                  { return b->getBorrowCount(); }, reverse);
        break;
    }
    return sortedBooks;
}

Array<Book *> BookManager::getAllBooks()
{
    return bookTable.all();
}