#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "models/Book.hpp"

class BookHashTable
{
private:
    std::unordered_map<std::string, Book> table;

public:
    BookHashTable() = default;
    ~BookHashTable() = default;

    BookHashTable(const BookHashTable &) = delete;
    BookHashTable &operator=(const BookHashTable &) = delete;

    bool empty() const { return table.empty(); }
    size_t size() const { return table.size(); }

    // Insert book if ISBN does not exist yet
    bool insert(const Book &b)
    {
        auto [it, inserted] = table.emplace(b.getISBN(), b);
        if(!inserted){
            cout << "Duplicated isbn" << endl;
        }
        return inserted;
    }

    // Find book by ISBN
    Book* find(const std::string &isbn)
    {
        auto it = table.find(isbn);
        if (it != table.end())
            return &(it->second);
        return nullptr;
    }

    // Remove book by ISBN
    bool erase(const std::string &isbn)
    {
        return table.erase(isbn) > 0;
    }

    // Remove all books
    void clear()
    {
        table.clear();
    }

    // Return all books as pointers for easy iteration
    std::vector<Book *> all()
    {
        std::vector<Book *> out;
        out.reserve(table.size());
        for (auto &pair : table)
            out.push_back(&pair.second);
        return out;
    }
};
