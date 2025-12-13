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
    unordered_map<string, vector<Book*>> titleIndex;
    unordered_map<string, vector<Book*>> authorIndex;

public:
    BookSearchMap() = default;

    // Build indices from a list of Book pointers
    void buildIndices(const vector<Book*>& books)
    {
        titleIndex.clear();
        authorIndex.clear();

        for (auto* b : books)
        {
            titleIndex[b->getTitle()].push_back(b);
            authorIndex[b->getAuthor()].push_back(b);
        }
    }

    // Search books by title
    vector<Book*> findByTitle(const string& title) const
    {
        auto it = titleIndex.find(title);
        if (it != titleIndex.end())
            return it->second;
        return {}; // empty if not found
    }

    // Search books by author
    vector<Book*> findByAuthor(const string& author) const
    {
        auto it = authorIndex.find(author);
        if (it != authorIndex.end())
            return it->second;
        return {}; // empty if not found
    }
};
