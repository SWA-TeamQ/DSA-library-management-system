#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "dsa/Array.hpp"
#include "core/LibraryController.hpp"
#include "ui/UiHelpers.hpp"
#include "ui/UiComponents.hpp"
#include "ui/Schemas.hpp"

class BookMenu
{
public:
    BookMenu(LibraryController &controller) : controller(controller) {};
    void show();

private:
    LibraryController &controller;

    void listBooks();
    void removeBook();
    void addBook();
    void updateBook();
    void searchBooks();
    void sortBooks();
};