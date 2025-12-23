#pragma once
#include <iostream>
#include <string>
#include "ui/UiHelpers.hpp"
#include "ui/BookMenu.hpp"
#include "ui/PatronMenu.hpp"
#include "ui/TransactionMenu.hpp"
#include "core/LibraryController.hpp"

using namespace std;

class ConsoleInterface
{
private:
    LibraryController controller;
    bool running{true};

    // --- Menus ---
    void printMainMenu() const;

    // --- Category Delegation ---
    void handleBookMenu();
    void handlePatronMenu();
    void handleTransactionMenu();
    void handleDataMenu();

    // --- Data Operations --- (kept here)
    void handleSaveData();
    void handleLoadData();

public:
    ConsoleInterface(LibraryController c) : controller(c) {}
    void run();
};
