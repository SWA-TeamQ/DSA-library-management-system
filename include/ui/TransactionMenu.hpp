#pragma once

#include <string>
#include "core/LibraryController.hpp"
#include "ui/UiHelpers.hpp"

class TransactionMenu
{
public:
    TransactionMenu(LibraryController &controller) : controller(controller) {}
    void show();

private:
    LibraryController &controller;

    void listTransactions();
    void addTransaction();
    void searchTransactions();
    void sortTransactions();
};
