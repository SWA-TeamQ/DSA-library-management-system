#pragma once
#include <string>
#include <iostream>
using namespace std;

class Book {
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
    Book(string t, string a, string i, string e, string py, string c, bool av, int bc)
        : title(move(t)), author(move(a)), isbn(move(i)), edition(move(e)), publicationYear(move(py)), category(move(c)), available(av), borrowCount(bc) {}

    

    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    const string& getISBN() const { return isbn; }
    const string& getEdition() const { return edition; }
    const string& getPublicationYear() const { return publicationYear; }
    const string& getCategory() const { return category; }
    bool isAvailable() const { return available; }
    int getBorrowCount() const { return borrowCount; }

    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setISBN(const string& i) { isbn = i; }
    void setEdition(const string& e) { edition = e; }
    void setPublicationYear(const string& py) { publicationYear = py; }
    void setCategory(const string& c) { category = c; }
    void setAvailable(bool v) { available = v; }
    void incrementBorrowCount() { ++borrowCount; }
    void decrementBorrowCount() { if (borrowCount > 0) --borrowCount; }
    void setBorrowCount(int bc) { borrowCount = bc; }

    void displayDetails(ostream& os = cout) const;
    void serialize(ostream &ofs) const; // write to stream (file)
    void deserialize(const string &line); // parse a line from file
};
