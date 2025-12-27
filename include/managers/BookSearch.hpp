#pragma once
#include "models/Book.hpp"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "utils/utils.hpp"

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
        string title = toLower(b.getTitle()), author = toLower(b.getAuthor()), category = toLower(b.getCategory());

        titleIndex[title].insert(b.getKey());
        authorIndex[author].insert(b.getKey());
        categoryIndex[category].insert(b.getKey());
    }

    void remove(Book &b)
    {
        string key = b.getKey(), title = toLower(b.getTitle()), author = toLower(b.getAuthor()), category = toLower(b.getCategory());
        auto removeIndex = [](unordered_map<string, unordered_set<string>> &index, string &key, string &value)
        {
            auto it = index.find(value);
            if (it != index.end())
            {
                it->second.erase(key);
                if (it->second.empty())
                {
                    index.erase(it);
                }
            }
        };

        removeIndex(titleIndex, key, title);
        removeIndex(authorIndex, key, author);
        removeIndex(categoryIndex, key, category);
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
