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
    bool available{true};
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
         bool available = true,
         int borrowCount = 0);

    // for generic lookup
    const string getKey() const { return isbn; }

    const string getTitle() const { return title; }
    const string getAuthor() const { return author; }
    const string getISBN() const { return isbn; }
    const string getEdition() const { return edition; }
    const int getPublicationYear() const { return publicationYear; }
    const string getCategory() const { return category; }
    const int getTotalQuantity() const { return TotalQuantity; }
    const int getCurrentQuantity() const { return currentQuantity; }
    bool isAvailable() const { return currentQuantity > 0; }
    int getBorrowCount() const { return borrowCount; }

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
    
    
    void setAvailable(bool available) { this->available = available; }
    void setBorrowCount(int bc) { borrowCount = bc; }

    void incrementBorrowCount() { ++borrowCount; }

    string serialize() const;
    void deserialize(const string &line);

    Array<string> getFields() const;
    Array<string> getValues() const;
};
