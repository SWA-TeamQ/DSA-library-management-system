#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "models/Book.hpp"

using namespace std;

// Simple search table for Books by title and author
class BookSearchMap
{
private:
    unordered_map<string, unordered_set<string>> titleIndex;
    unordered_map<string, unordered_set<string>> authorIndex;
    unordered_map<string, unordered_set<string>> categoryIndex;

public:
    BookSearchMap() = default;
    ~BookSearchMap() = default;

    void clear(){
        titleIndex.clear();
        authorIndex.clear();
        categoryIndex.clear();
    }

    // Build indices from a list of Books
    void buildIndices(const vector<Book>& books)
    {
        clear();
        for(const auto &b : books){
            insert(b);
        }
    }

    void insert(const Book& b)
    {
        titleIndex[b.getTitle()].insert(b.getKey());
        authorIndex[b.getAuthor()].insert(b.getKey());
        categoryIndex[b.getCategory()].insert(b.getKey());
    }

    void remove(const Book& b)
    {
        string id = b.getKey(), title = b.getTitle(), author = b.getAuthor(), category = b.getCategory();
        
        auto it = titleIndex.find(title);
        if(it != titleIndex.end())
            it->second.erase(id);

        it = authorIndex.find(author);
        if(it != authorIndex.end())
            it->second.erase(id);

        it = categoryIndex.find(category);
        if(it != categoryIndex.end())
            it->second.erase(id);
    }

    // Search books by title
    vector<string> findByTitle(const string& title) const
    {
        auto it = titleIndex.find(title);
        if (it != titleIndex.end())
            return vector<string>(it->second.begin(), it->second.end());
        return {};
    }

    // Search books by author
    vector<string> findByAuthor(const string& author) const
    {
        auto it = authorIndex.find(author);
        if (it != authorIndex.end())
            return vector<string>(it->second.begin(), it->second.end());
        return {};
    }

    // Search books by category
    vector<string> findByCategory(const string& category) const
    {
        auto it = categoryIndex.find(category);
        if (it != categoryIndex.end())
            return vector<string>(it->second.begin(), it->second.end());
        return {};
    }
};
