#pragma once
#include "core/LibraryController.hpp"
#include <string>
#include <iostream>
#include "models/Patron.hpp"
#include "models/Book.hpp"
#include "models/Transaction.hpp"
#include "dsa/Array.hpp"

using namespace std;
class ConsoleInterface
{
private:
    LibraryController controller;
    bool running{true};

    // --- UI Helpers ---
    void clearScreen() const;
    void printDivider() const;
    void printHeader(const string &title) const;
    void waitForEnter() const;
    string getInput(const string &prompt) const;
    void printWelcomeBanner() const;

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
    // Patron Management 
    void handleAddPatron();
    
    // handles listing of all the patrons 
   void ConsoleInterface::handleListPatrons()
{
    printHeader("All Patrons");
    controller.listAllPatrons();
    waitForEnter();
}

    // handles patrons search
  void ConsoleInterface::handleSearchPatrons()
{
    printHeader("Search Patron by Name");

    string name = getInput("Enter patron name: ");
    Patron* p = controller.findPatronByName(name);

    if (!p)
    {
        cout << "No patron found.\n";
    }
    else
    {
        printDivider();
        p->displayDetails();
    }

    waitForEnter();
}

 // handles patrons removal
 void ConsoleInterface::handleRemovePatron()
{
    printHeader("Remove Patron");

    string id = getInput("Enter Patron ID: ");

    if (controller.removePatron(id))
        cout << "Patron removed successfully.\n";
    else
        cout << "Cannot remove patron (active loans or not found).\n";

    waitForEnter();
}



    // --- Transaction Operations ---
    void handleBorrow();
    void handleReturn();
    void handleViewHistory(); // Placeholder for Member 4

    // --- Data Operations ---
    void handleSaveData(); // Placeholder for Member 6
    void handleLoadData(); // Placeholder for Member 6

public:
    ConsoleInterface(LibraryController c){
        controller = c;
    }
    void run();
};
