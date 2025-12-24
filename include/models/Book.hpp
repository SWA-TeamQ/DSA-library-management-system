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
    int TotalQuantity;
    int currentQuantity;
    int borrowCount{0};

public:
    Book() = default;

    Book(string title,
         string author,
         string isbn,
         string edition,
         int publicationYear,
         string category = "General",
         int TotalQuantity = 1,
         int currentQuantity = 1,
         int borrowCount = 0);

    // for generic lookup
    const string getKey() { return isbn; }

    const string getTitle() { return title; }
    const string getAuthor() { return author; }
    const string getISBN() { return isbn; }
    const string getEdition() { return edition; }
    const int getPublicationYear() { return publicationYear; }
    const string getCategory()  { return category; }
    const int getTotalQuantity()  { return TotalQuantity; }
    const int getCurrentQuantity()  { return currentQuantity; }
    const bool isAvailable() {return currentQuantity > 0;}
    int getBorrowCount()  { return borrowCount; }

    void setTitle(const string &title) { this->title = title; }
    void setAuthor(const string &author) { this->author = author; }
    void setISBN(const string &isbn) { this->isbn = isbn; }
    void setEdition(const string &edition) { this->edition = edition; }
    void setPublicationYear(const int &publicationYear) { this->publicationYear = publicationYear; }
    void setCategory(const string &category) { this->category = category; }
    void setTotalQuantity(const int &TotalQuantity) { this->TotalQuantity = TotalQuantity; }
    void incrementCurrentQuantity() { this->currentQuantity++; }
    void decrementCurrentQuantity() { this->currentQuantity--; }
    bool isAllReturned() { return currentQuantity == TotalQuantity; }
    void setBorrowCount(int bc) { borrowCount = bc; }

    void incrementBorrowCount() { ++borrowCount; }

    string serialize();
    void deserialize(const string &line);

    Array<string> getFields();
    Array<string> getValues();
};
