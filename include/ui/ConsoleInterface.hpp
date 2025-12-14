#pragma once
#include "core/LibraryController.hpp"
#include <string>
#include <iostream>
using namespace std;

class ConsoleInterface
{
private:
    LibraryController &controller;
    bool running{true};

    // --- UI Helpers ---
    void clearScreen() const;
    void printHeader(const string &title) const;
    void waitForEnter() const;
    string getInput(const string &prompt) const;
    void printDivider() const;

    // --- Menus ---
    void printMainMenu() const;

    // --- Sub-Menus / Categories ---
    void handleBookMenu();
    void handlePatronMenu();
    void handleTransactionMenu();
    void handleDataMenu();

    // --- Book Operations ---
    void handleAddBook();
    void handleListBooks();
    void handleSearchBooks(); // Placeholder for Member 2
    void handleSortBooks();   // Placeholder for Member 2
    void handleRemoveBook();  // Placeholder for Member 2

    // --- Member Operations ---
    void handleAddPatron();
    void handleListPatrons();
    void handleSearchPatrons(); // Placeholder for Member 3
    void handleRemovePatron();  // Placeholder for Member 3

    // --- Transaction Operations ---
    void handleBorrow();
    void handleReturn();
    void handleViewHistory(); // Placeholder for Member 4

    // --- Data Operations ---
    void handleSaveData(); // Placeholder for Member 6
    void handleLoadData(); // Placeholder for Member 6

public:
    explicit ConsoleInterface(LibraryController &c) : controller(c) {}
    void run();
};
