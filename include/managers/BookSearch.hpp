#pragma once
#include "models/Book.hpp"
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

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
    void buildIndices(const unordered_map<string, Book>& books)
    {
        clear();
        for(const auto &[id, book] : books){
            insert(book);
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
        
        // remove from titleIndex
        auto it = titleIndex.find(title);
        if(it != titleIndex.end()){
            it->second.erase(id);
            // after deletion if the unordered set is empty, then we want to remove the key
            if(it->second.empty()){
                titleIndex.erase(it);
            }
        }

        // remove from authorIndex
        it = authorIndex.find(author);
        if(it != authorIndex.end()){
            it->second.erase(id);
            // after deletion if the unordered set is empty, then we want to remove the key
            if(it->second.empty()){
                authorIndex.erase(it);
            }
        }

        // remove from categoryIndex
        it = categoryIndex.find(category);
        if(it != categoryIndex.end()){
            it->second.erase(id);
            // after deletion if the unordered set is empty, then we want to remove the key
            if(it->second.empty()){
                categoryIndex.erase(it);
            }
        }
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
