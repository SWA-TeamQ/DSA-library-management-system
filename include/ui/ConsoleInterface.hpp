#pragma once

#include "core/LibraryController.hpp"
#include <string>

class ConsoleInterface
{
private:
    LibraryController controller;
    bool running{true};

    // --- UI Helpers ---
    void clearScreen() const;
    void printDivider() const;
    void printHeader(const std::string &title) const;
    void waitForEnter() const;
    std::string getInput(const std::string &prompt) const;
    void printWelcomeBanner() const;

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
    explicit ConsoleInterface(LibraryController c) : controller(c) {}
    void run();
};
