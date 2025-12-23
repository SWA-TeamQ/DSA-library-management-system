#pragma once

#include <string>
#include "dsa/Array.hpp"
#include "core/LibraryController.hpp"

class BookMenu
{
public:
    explicit BookMenu(LibraryController &controller);
    void show();

private:
    LibraryController &controller;

    void listBooks();
    void addBook();
    void removeBook();
    void searchBooks();
    void sortBooks();

    void printBooksTable(const Array<Book *> &books) const;
    std::string readLine(const std::string &prompt) const;
    int readInt(const std::string &prompt) const;
    void waitForEnter() const;
};