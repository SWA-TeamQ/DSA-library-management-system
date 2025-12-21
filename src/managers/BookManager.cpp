#include <iostream>
#include <algorithm>
#include <cctype>
#include "managers/BookManager.hpp"
#include "dsa/MergeSort.hpp"

using namespace std;

// trim whitespace from a string
string trim(const string &s)
{
    auto start = find_if_not(s.begin(), s.end(), ::isspace);
    auto end = find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    return (start < end ? string(start, end) : "");
}

void BookManager::loadBooks()
{
    bookStore.loadData(bookList); // load from books.txt
    for (auto &b : bookList)
        books.insert(&b); // insert into hash table
    buildSearchIndex();
}

bool BookManager::removeBook(const BookSearchKey key, const string &value)
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
    vector<string> ids;
    switch(key){
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

    if(ids.empty()){
        return nullptr;
    }

    Book *book = bookTable.find(ids[0]);
    if (book) {
        return book;
    }
    return nullptr;
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
    Book *oldBook = bookTable.find(newBook.getKey());
    if(oldBook == nullptr){
        return false;
    }

    bool changed = false;
    int publicationYear = -1; // check if publicationYear is changed

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
    }

    return changed;
}


vector<Book *> BookManager::sortBooks(const BookSortKey key, bool reverse){
    vector<Book *> sortedBooks = bookTable.all();

    switch(key){
        case BookSortKey::TITLE:
            mergeSort(sortedBooks, [](const Book *b){
                return b->getTitle();
            }, reverse);
            break;
        case BookSortKey::AUTHOR:
            mergeSort(sortedBooks, [](const Book *b){
                return b->getAuthor();
            }, reverse);
            break;
        case BookSortKey::YEAR:
            mergeSort(sortedBooks, [](const Book *b){
                return b->getPublicationYear();
            }, reverse);
            break;
        case BookSortKey::BORROW_COUNT:
            mergeSort(sortedBooks, [](const Book *b){
                return b->getBorrowCount();
            }, reverse);
            break;
    }
    return sortedBooks;
}