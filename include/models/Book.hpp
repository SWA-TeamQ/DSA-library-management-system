#pragma once
#include <string>
#include <iostream>
#include "dsa/Array.hpp"
using namespace std;

enum class BookSearchKey
{
    ID,
    TITLE,
    AUTHOR,
    CATEGORY
};

enum class BookSortKey
{
    TITLE,
    AUTHOR,
    YEAR,
    BORROW_COUNT
};

class Book
{
private:
    string isbn;
    string title;
    string author;
    string edition;
    int publicationYear;
    string category;
    int totalQuantity;
    int currentQuantity;
    int borrowCount;

public:
    Book() = default;

    Book(
        string isbn,
        string title,
        string author,
        string edition,
        int publicationYear,
        string category = "General",
        int totalQuantity = 1) : isbn(move(isbn)),
                                 title(move(title)),
                                 author(move(author)),
                                 edition(move(edition)),
                                 publicationYear(publicationYear),
                                 category(move(category)),
                                 totalQuantity(totalQuantity),
                                 currentQuantity(totalQuantity),
                                 borrowCount(0)
    {
    }

    // for generic lookup
    string &getKey() { return isbn; }

    string &getTitle() { return title; }
    string &getAuthor() { return author; }
    string getEdition() { return edition; }
    int getPublicationYear() { return publicationYear; }
    string &getCategory() { return category; }
    int getTotalQuantity() { return totalQuantity; }
    int getCurrentQuantity() { return currentQuantity; }
    bool isAvailable() { return currentQuantity > 0; }
    int getBorrowCount() { return borrowCount; }

    void setTitle(string t) { this->title = t; }
    void setAuthor(string a) { this->author = a; }
    void setISBN(string i) { this->isbn = i; }
    void setEdition(string e) { this->edition = e; }
    void setPublicationYear(int p) { this->publicationYear = p; }
    void setCategory(string c) { this->category = c; }
    void setTotalQuantity(int t) { this->totalQuantity = t; }
    void incrementCurrentQuantity()
    {
        if (currentQuantity < totalQuantity)
            this->currentQuantity++;
    }
    void decrementCurrentQuantity()
    {
        if (currentQuantity > 0)
            this->currentQuantity--;
    }

    bool isAllReturned() { return this->currentQuantity == this->totalQuantity; }
    void setBorrowCount(int b) { this->borrowCount = b; }
    void incrementBorrowCount() { this->borrowCount++; }

    string serialize();
    void deserialize(string line);

    // Key-based access helpers (string keys per schema: isbn, title, ...)
    // Returns value stringified; empty string if key unknown.
    string getField(const string &key);
    // Sets field from string; parses integers when needed. Returns true if key handled.
    bool setField(const string &key, const string &value);

    Array<string> getFields();
    Array<string> getValues();
};
