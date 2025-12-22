#pragma once
#include "models/Book.hpp"
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "dsa/Array.hpp"

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

    void clear()
    {
        titleIndex.clear();
        authorIndex.clear();
        categoryIndex.clear();
    }

    // Build indices from any map-like container of Books (e.g., unordered_map, HashTable)
    template <typename MapType>
    void buildIndices(const MapType &books)
    {
        clear();
        for (const auto &[id, book] : books)
        {
            insert(book);
        }
    }

    void insert(const Book &b)
    {
        titleIndex[b.getTitle()].insert(b.getKey());
        authorIndex[b.getAuthor()].insert(b.getKey());
        categoryIndex[b.getCategory()].insert(b.getKey());
    }

    void remove(const Book &b)
    {
        string id = b.getKey(), title = b.getTitle(), author = b.getAuthor(), category = b.getCategory();

        // remove from titleIndex
        auto it = titleIndex.find(title);
        if (it != titleIndex.end())
        {
            it->second.erase(id);
            // after deletion if the unordered set is empty, then we want to remove the key
            if (it->second.empty())
            {
                titleIndex.erase(it);
            }
        }

        // remove from authorIndex
        it = authorIndex.find(author);
        if (it != authorIndex.end())
        {
            it->second.erase(id);
            // after deletion if the unordered set is empty, then we want to remove the key
            if (it->second.empty())
            {
                authorIndex.erase(it);
            }
        }

        // remove from categoryIndex
        it = categoryIndex.find(category);
        if (it != categoryIndex.end())
        {
            it->second.erase(id);
            // after deletion if the unordered set is empty, then we want to remove the key
            if (it->second.empty())
            {
                categoryIndex.erase(it);
            }
        }
    }

    // Search books by title
    Array<string> findByTitle(const string &title) const
    {
        auto it = titleIndex.find(title);
        if (it != titleIndex.end())
        {
            auto setIt = it->second;
            Array<string> ids;
            for (auto &key : setIt)
            {
                ids.append(key);
            }
            return ids;
        }
        return {};
    }

    // Search books by author
    Array<string> findByAuthor(const string &author) const
    {
        auto it = authorIndex.find(author);
        if (it != authorIndex.end())
        {
            auto setIt = it->second;
            Array<string> ids;
            for (auto &key : setIt)
            {
                ids.append(key);
            }
            return ids;
        }

        return {};
    }

    // Search books by category
    Array<string> findByCategory(const string &category) const
    {
        auto it = categoryIndex.find(category);
        if (it != categoryIndex.end())
        {
            auto setIt = it->second;
            Array<string> ids;
            for (auto &key : setIt)
            {
                ids.append(key);
            }
            return ids;
        }

        return {};
    }
};
