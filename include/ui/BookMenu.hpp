#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "dsa/Array.hpp"
#include "core/LibraryController.hpp"
#include "ui/UiHelpers.hpp"

class BookMenu
{
public:
    BookMenu(LibraryController &controller) : controller(controller) {};
    void show();

private:
    LibraryController &controller;

    void listBooks();
    void addBook();
    void removeBook();
    void updateBook();
    void searchBooks();
    void sortBooks();
};