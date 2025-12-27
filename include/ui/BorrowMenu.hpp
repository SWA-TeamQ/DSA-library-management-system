#pragma once
#include <iostream>
#include <string>
#include "core/LibraryController.hpp"
#include "ui/UiHelpers.hpp"
#include "ui/UiComponents.hpp"
#include "ui/Schemas.hpp"

class BorrowMenu
{
private:
    LibraryController &controller;
public:
    BorrowMenu(LibraryController &controller) : controller(controller) {}
    void show();


    void borrowBook();
    void returnBook();
};
