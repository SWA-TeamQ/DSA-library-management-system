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
        string key = b.getKey(), title = b.getTitle(), author = b.getAuthor(), category = b.getCategory();

        removeIndex(titleIndex, key, title);
        removeIndex(authorIndex, key, author);
        removeIndex(categoryIndex, key, category);
    }

    Array<string> findByTitle(string title)
    {
        return findIds(titleIndex, title);
    }

    Array<string> findByAuthor(string author)
    {
        return findIds(authorIndex, author);
    }

    Array<string> findByCategory(string category)
    {
        return findIds(categoryIndex, category);
    }
};
