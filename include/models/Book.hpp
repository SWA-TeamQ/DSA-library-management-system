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
    string title;
    string author;
    string isbn;
    string edition;
    int publicationYear;
    string category;
    int totalQuantity;
    int currentQuantity;
    int borrowCount;

public:
    Book() = default;

    Book(string title,
         string author,
         string isbn,
         string edition,
         int publicationYear,
         string category = "General",
         int totalQuantity = 1,
         int currentQuantity = 1,
         int borrowCount = 0);

    // for generic lookup
    const string& getKey() const { return isbn; }
    
    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    const string getEdition() { return edition; }
    int getPublicationYear() const { return publicationYear; }
    const string& getCategory() const { return category; }
    int getTotalQuantity() const { return totalQuantity; }
    int getCurrentQuantity() const { return currentQuantity; }
    bool isAvailable() const { return currentQuantity > 0; }
    int getBorrowCount()  { return borrowCount; }

    void setTitle(const string &t) { this->title = t; }
    void setAuthor(const string &a) { this->author = a; }
    void setISBN(const string &i) { this->isbn = i; }
    void setEdition(const string &e) { this->edition = e; }
    void setPublicationYear(const int &p) { this->publicationYear = p; }
    void setCategory(const string &c) { this->category = c; }
    void setTotalQuantity(const int &t) { this->totalQuantity = t; }
    void incrementCurrentQuantity() { if(currentQuantity < totalQuantity) this->currentQuantity++; }
    void decrementCurrentQuantity() { if(currentQuantity > 0) this->currentQuantity--; }

    bool isAllReturned() { return currentQuantity == totalQuantity; }
    void setBorrowCount(int b) { this->borrowCount = b; }
    void incrementBorrowCount() { this->borrowCount++; }

    string serialize() const;
    void deserialize(const string &line);

    Array<string> getFields();
    Array<string> getValues();
};
