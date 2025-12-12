#pragma once
#include <string>
#include <iostream>
using namespace std;

class Book
{
private:
    string title;
    string author;
    string isbn;
    string edition;
    string publicationYear;
    string category;
    bool available{true};
    int borrowCount{0};

public:
    Book() = default;

    Book(string title = "",
         string author = "",
         string isbn = "",
         string edition = "",
         string publicationYear = "",
         string category = "General",
         bool available = true,
         int borrowCount = 0);

    const string &getTitle() const { return title; }
    const string &getAuthor() const { return author; }
    const string &getISBN() const { return isbn; }
    const string &getEdition() const { return edition; }
    const string &getPublicationYear() const { return publicationYear; }
    const string &getCategory() const { return category; }
    bool isAvailable() const { return available; }
    int getBorrowCount() const { return borrowCount; }

    void setTitle(const string &title) { this->title = title; }
    void setAuthor(const string &author) { this->author = author; }
    void setISBN(const string &isbn) { this->isbn = isbn; }
    void setEdition(const string &edition) { this->edition = edition; }
    void setPublicationYear(const string &publicationYear) { this->publicationYear = publicationYear; }
    void setCategory(const string &category) { this->category = category; }
    void setAvailable(bool available) { this->available = available; }
    void setBorrowCount(int bc) { borrowCount = bc; }

    void incrementBorrowCount() { ++borrowCount; }
    void decrementBorrowCount()
    {
        if (borrowCount > 0)
            --borrowCount;
    }

    void displayDetails() const;
    string serialize() const;
    void deserialize(const string &line);
};
