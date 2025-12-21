#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "models/Book.hpp"

using namespace std;

// Simple search table for Books by title and author
class BookSearchMap
{
private:
    unordered_map<string, vector<string>> titleIndex;
    unordered_map<string, vector<string>> authorIndex;

public:
    BookSearchMap() = default;
    ~BookSearchMap() = default;

    // Build indices from a list of Books
    void buildIndices(const vector<Book>& books)
    {
        titleIndex.clear();
        authorIndex.clear();

        for(auto b : books){
            titleIndex[b.getTitle()].push_back(b.getISBN());
            authorIndex[b.getAuthor()].push_back(b.getISBN());
        }
    }

    void addBook(const Book& b)
    {
        titleIndex[b.getTitle()].push_back(b.getISBN());
        authorIndex[b.getAuthor()].push_back(b.getISBN());
    }

    void removeBook(const Book& b)
    {
        titleIndex[b.getTitle()].remove(b.getISBN());
        authorIndex[b.getAuthor()].remove(b.getISBN());
    }

    // Search books by title
    vector<string> findByTitle(const string& title) const
    {
        auto it = titleIndex.find(title);
        if (it != titleIndex.end())
            return it->second;
        return {};
    }

    // Search books by author
    vector<string> findByAuthor(const string& author) const
    {
        auto it = authorIndex.find(author);
        if (it != authorIndex.end())
            return it->second;
        return {};
    }
};
