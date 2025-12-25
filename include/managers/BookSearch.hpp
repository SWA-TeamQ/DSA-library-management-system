#pragma once
#include "models/Book.hpp"
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

// Simple search table for Books by title, author, category
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
        titleIndex[b.getTitle()].insert(b.getKey());
        authorIndex[b.getAuthor()].insert(b.getKey());
        categoryIndex[b.getCategory()].insert(b.getKey());
    }

    void remove(Book &b)
    {
        string key = b.getKey(), title = b.getTitle(), author = b.getAuthor(), category = b.getCategory();
        auto removeIndex = [](unordered_map<string, unordered_set<string>> &index, string value)
        {
            auto it = index.find(value);
            if (it != index.end())
            {
                if (it->second.empty())
                {
                    index.erase(it);
                }
            }
        };

        removeIndex(titleIndex, b.getTitle());
        removeIndex(authorIndex, b.getAuthor());
        removeIndex(categoryIndex, b.getCategory());
    }

    Array<string> findByTitle(string title)
    {
        Array<string> result;
        auto ids = titleIndex.at(title);
        for (auto &id : ids)
        {
            result.append(id);
        }
        return result;
    }

    Array<string> findByAuthor(string author)
    {
        Array<string> result;
        auto ids = authorIndex.at(author);
        for (auto &id : ids)
        {
            result.append(id);
        }
        return result;
    }

    Array<string> findByCategory(string category)
    {
        Array<string> result;
        auto ids = categoryIndex.at(category);
        for (auto &id : ids)
        {
            result.append(id);
        }
        return result;
    }
};
