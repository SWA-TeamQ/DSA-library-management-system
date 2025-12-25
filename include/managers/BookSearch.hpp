#pragma once
#include "models/Book.hpp"
#include "dsa/Map.hpp"
#include "dsa/Array.hpp"
#include <string>

using namespace std;

// Simple search table for Books by title, author, category
class BookSearchMap
{
private:
    dsa::unordered_map<string, dsa::Array<string>> titleIndex;
    dsa::unordered_map<string, dsa::Array<string>> authorIndex;
    dsa::unordered_map<string, dsa::Array<string>> categoryIndex;

public:
    BookSearchMap() = default;
    ~BookSearchMap() = default;

    void clear()
    {
        titleIndex.clear();
        authorIndex.clear();
        categoryIndex.clear();
    }

    // Build indices from any map-like container of Books
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
        titleIndex[b.getTitle()].append(b.getKey());
        authorIndex[b.getAuthor()].append(b.getKey());
        categoryIndex[b.getCategory()].append(b.getKey());
    }

    void remove(const Book &b)
    {
        auto removeFromIndex = [&](dsa::unordered_map<string,Array<string>> &index, const string &key)
        {
            Array<string>* arrPtr = index.find(key);
            if (arrPtr)
            {
                Array<string>& arr = *arrPtr;
                for (size_t i = 0; i < arr.size(); i++)
                {
                    if (arr[i] == b.getKey())
                    {
                        arr.removeAt(i);
                        break;
                    }
                }
                if (arr.isEmpty())
                {
                    index.erase(key);
                }
            }
        };

        removeFromIndex(titleIndex, b.getTitle());
        removeFromIndex(authorIndex, b.getAuthor());
        removeFromIndex(categoryIndex, b.getCategory());
    }

    Array<string> findByTitle(const string &title) const
    {
        try
        {
            return titleIndex.at(title); // throws if key not found
        }
        catch (std::out_of_range &)
        {
            return {};
        }
    }

    dsa::Array<string> findByAuthor(const string &author) const
    {
        try
        {
            return authorIndex.at(author);
        }
        catch (std::out_of_range &)
        {
            return {};
        }
    }

    dsa::Array<string> findByCategory(const string &category) const
    {
        try
        {
            return categoryIndex.at(category);
        }
        catch (std::out_of_range &)
        {
            return {};
        }
    }
};
