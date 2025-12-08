#pragma once
#include "LibraryController.hpp"
#include <string>
using namespace std;

class ConsoleInterface {
private:
    LibraryController& controller;
    bool running{true};

    void printMainMenu() const;
    void handleAddBook();
    void handleListBooks();
    void handleAddPatron();
    void handleListPatrons();
    void handleBorrow();
    void handleReturn();
public:
    explicit ConsoleInterface(LibraryController& c) : controller(c) {}
    void run();
};
