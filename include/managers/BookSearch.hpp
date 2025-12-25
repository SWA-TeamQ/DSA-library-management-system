#pragma once
#include "models/Book.hpp"
#include <unordered_map>
#include "dsa/Array.hpp"
#include <string>

using namespace std;

// Simple search table for Books by title, author, category
class BookSearchMap
{
private:
    unordered_map<string, Array<string>> titleIndex;
    unordered_map<string, Array<string>> authorIndex;
    unordered_map<string, Array<string>> categoryIndex;

public:
    BookSearchMap() = default;
    ~BookSearchMap() = default;

    void clear()
    {
        titleIndex.clear();
        authorIndex.clear();
        categoryIndex.clear();
    }

    void buildIndices(HashTable<Book> &books)
    {
        clear();
        for (auto &[id, book] : books)
        {
            insert(book);
        }
    }

    void insert(Book &b)
    {
        titleIndex[b.getTitle()].append(b.getKey());
        authorIndex[b.getAuthor()].append(b.getKey());
        categoryIndex[b.getCategory()].append(b.getKey());
    }

    void remove(Book &b)
    {
        auto removeFromIndex = [&](unordered_map<string, Array<string>> &index, string key)
        {
            auto it = index.find(key);
            if (it != index.end())
            {
                auto &arr = it->second;
                for (size_t i = 0; i < arr.size(); i++)
                {
                    if (arr[i] == b.getKey())
                    {
                        arr.removeAt(i);
                        break;
                    }
                }
                if (arr.empty())
                {
                    index.erase(it);
                }
            }
        };

        removeFromIndex(titleIndex, b.getTitle());
        removeFromIndex(authorIndex, b.getAuthor());
        removeFromIndex(categoryIndex, b.getCategory());
    }

    Array<string> findByTitle(string title)
    {
        return titleIndex.at(title);
    }

    Array<string> findByAuthor(string author)
    {
        return authorIndex.at(author);
    }

    Array<string> findByCategory(string category)
    {
        return categoryIndex.at(category);
    }
};
