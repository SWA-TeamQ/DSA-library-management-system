#include "core/LibraryController.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include "managers/BookManager.hpp"

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
        books.insert(b); // insert into hash table
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
    if (books.insert(bookList.back()))
    {
        bookStore.addData(bookList.back()); // persist after addition
        buildSearchIndex();
        return true;
    }
    else
    {
        bookList.pop_back();
        return false;
    }
}

// Remove a book by its ISBN
bool BookManager::removeBookByISBN(const string &isbn)
{
    Book *book = books.find(isbn);
    if (!book)
        return false;

    if (book->getBorrowCount() > 0)
    {
        cout << "Cannot remove: some copies are on loan." << endl;
        return false;
    }

    books.erase(isbn); // remove the book from the hash table

    saveBooks();
    buildSearchIndex();
    return true;
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
            return a.getPublicationYear()> b.getPublicationYear();
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
Book *BookManager::updateBookDetails(const string &isbn, const string &title, const string &author, const string &edition, const int &publicationYear, const string &category, const int &quantity, bool available, int borrowCount)
{
    Book *b = findBookByISBN(isbn);
    if (!b)
    {
        return nullptr;
    }

    bool changed = false;
    int publicationYear = -1; // check if publicationYear is changed

    string trimmedTitle = trim(title);
    if (!trimmedTitle.empty())
    {
        b->setTitle(trimmedTitle);
        changed = true;
    }

    string trimmedAuthor = trim(author);
    if (!trimmedAuthor.empty())
    {
        b->setAuthor(trimmedAuthor);
        changed = true;
    }

    string trimmedEdition = trim(edition);
    if (!trimmedEdition.empty())
    {
        b->setEdition(trimmedEdition);
        changed = true;
    }

    if (publicationYear != -1)
    { // sentinel check
        b->setPublicationYear(publicationYear);
        changed = true;
    }

    string trimmedCategory = trim(category);
    if (!trimmedCategory.empty())
    {
        b->setCategory(trimmedCategory);
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