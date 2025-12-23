#pragma once
#include <string>
#include "dsa/Array.hpp"
#include "core/LibraryController.hpp"

class BookMenu
{
public:
    BookMenu(LibraryController &controller);
    void show();

private:
    LibraryController &controller;

    void listBooks();
    void addBook();
    void removeBook();
    void searchBooks();
    void sortBooks();
};