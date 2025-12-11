#pragma once
#include <string>
#include <iostream>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    string category;
    bool available{true};
    int borrowCount{0};
    
public:
    Book() = default;
    Book(string t, string a, string i, string c)
        : title(move(t)), author(move(a)), isbn(move(i)), category(move(c)) {}

    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    const string& getISBN() const { return isbn; }
    const string& getCategory() const { return category; }
    bool isAvailable() const { return available; }
    int getBorrowCount() const { return borrowCount; }

    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setISBN(const string& i) { isbn = i; }
    void setCategory(const string& c) { category = c; }
    void setAvailable(bool v) { available = v; }
    void incrementBorrowCount() { ++borrowCount; }

    void displayDetails(ostream& os = cout) const;
};
