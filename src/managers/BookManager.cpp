#include "managers/BookManager.hpp"
#include <algorithm>

void BookManager::loadBooks()
{
    store.loadData(books);
}

void BookManager::saveBooks() const
{
    store.saveData(books);
}

void BookManager::add(const Book &b)
{
    books.push_back(b);
    store.addData(b);
}

void BookManager::remove(const string &isbn)
{
    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if (it != books.end())
        {
            books.erase(it);
            saveBooks(); // Save after removal
        }
    }
}

void BookManager::displayAll() const
{
    for (const auto &book : books)
    {
        book.displayDetails();
    }
}