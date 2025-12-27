#pragma once
#include <iostream>
#include <string>
#include "core/LibraryController.hpp"
#include "ui/UiHelpers.hpp"
#include "ui/UiComponents.hpp"
#include "ui/Schemas.hpp"

class TransactionMenu
{
public:
    TransactionMenu(LibraryController &controller) : controller(controller) {}
    void show();

private:
    LibraryController &controller;

    void listTransactions();
    void listTransactionsForPatron();
    void listOverdueForPatron();
    void listTransactionsForBook();
    void searchTransactions();
    void sortTransactions();
};
