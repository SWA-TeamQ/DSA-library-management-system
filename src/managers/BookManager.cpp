#include "core/LibraryController.hpp"
#include <iostream>
#include "managers/BookManager.hpp"

using namespace std;

void BookManager::loadBooks()
{
    bookStore.loadData(bookList); // load from books.txt
    for (auto &b : bookList)
        books.insert(&b); // insert into hash table
    buildSearchIndex();
}

void BookManager::saveBooks()
{
    bookList.clear();
    for (auto *b : books.all())
        bookList.push_back(*b);
    bookStore.saveData(bookList); // save to books.txt
}

bool BookManager::addBook(const Book &b)
{
    bookList.push_back(b);
    if (books.insert(&bookList.back()))
    {
        saveBooks(); // persist after addition
        buildSearchIndex();
        return true;
    }
    else
    {
        bookList.pop_back();
        return false;
    }
}

bool BookManager::removeBookByISBN(const string &isbn)
{
    if (books.erase(isbn))
    {
        saveBooks(); // persist after removal
        buildSearchIndex();
        return true;
    }
    return false;
}
// Search a Book by its Id
Book *BookManager::findBookByISBN(const string &isbn) const
{
    return books.find(isbn);
}

void BookManager::sortBooksByTitle(bool reverse)
{
    mergeSort(bookList, [reverse](const Book &a, const Book &b)
              {
        if(reverse){
            return a.getTitle() > b.getTitle();
        }
        return a.getTitle() < b.getTitle(); });

    // Update the book store file with the sorted list
    bookStore.saveData(bookList);
}

// Sort a books by its publication year in ascending order
void BookManager::sortBooksByYear(bool reverse)
{
    mergeSort(bookList, [reverse](const Book &a, const Book &b)
              {
        if(reverse){
            return a.getPublicationYear() > b.getPublicationYear();
        }
        return a.getPublicationYear() < b.getPublicationYear(); });

    // Update the book store file with the sorted list
    bookStore.saveData(bookList);
}

// Build the search indices
void BookManager::buildSearchIndex()
{
    vector<Book *> bookPtrs;
    for (auto *b : books.all())
        bookPtrs.push_back(b);

    searchMap.buildIndices(bookPtrs);
}

// Search by title
vector<Book *> BookManager::findBooksByTitle(const string &title) const
{
    return searchMap.findByTitle(title);
}

// Search by author
vector<Book *> BookManager::findBooksByAuthor(const string &author) const
{
    return searchMap.findByAuthor(author);
}

// Update a book details
Book *BookManager::updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const string &publicationYear, const string &category, bool available, int borrowCount)
{
    Book *b = findBookByISBN(isbn);
    if (!b)
    {
        return nullptr;
    }

    bool changed = false;

    if (!title.empty())
    {
        b->setTitle(title);
        changed = true;
    }
    if (!author.empty())
    {
        b->setAuthor(author);
        changed = true;
    }
    if (!edition.empty())
    {
        b->setEdition(edition);
        changed = true;
    }
    if (!publicationYear.empty())
    {
        b->setPublicationYear(publicationYear);
        changed = true;
    }
    if (!category.empty())
    {
        b->setCategory(category);
        changed = true;
    }

    if (b->isAvailable() != available)
    {
        b->setAvailable(available);
        changed = true;
    }
    if (b->getBorrowCount() != borrowCount)
    {
        b->setBorrowCount(borrowCount);
        changed = true;
    }

    if (changed)
    {
        saveBooks(); // persist after update
        buildSearchIndex();
    }

    return b;
}

// display all books to the console
void BookManager::listAllBooks() const
{
    cout << "--- Books ---\n";
    for (auto *b : books.all())
        b->displayDetails();
}