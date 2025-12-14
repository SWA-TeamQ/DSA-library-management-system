#pragma once
#include <vector>
#include "models/Book.hpp"
#include "core/DataStore.hpp"

class BookManager {
private:
    vector<Book> books;
    DataStore<Book> store;

public:
    BookManager(const string& filename) : store(filename) {
        loadBooks();
    }

    void loadBooks();
    void saveBooks() const;

    void add(const Book& b);
    void remove(const string& isbn);

    void displayAll() const;
};
