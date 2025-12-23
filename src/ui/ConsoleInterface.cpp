#include "ui/ConsoleInterface.hpp"
#include "ui/BookMenu.hpp"
#include "ui/PatronMenu.hpp"
#include "ui/TransactionMenu.hpp"
#include <iostream>
#include <cstdlib> // for system()
#include <limits>
using namespace std;

// --- UI Helpers ---

void ConsoleInterface::clearScreen() const
{
    system("cls");
}

void ConsoleInterface::printDivider() const
{
    cout << "+------------------------------------------------------------+\n";
}

void ConsoleInterface::printWelcomeBanner() const
{
    clearScreen();
    cout << "  __________________________________________________________  \n";
    cout << " /                                                          \\ \n";
    cout << "|    ____________________________________________________    |\n";
    cout << "|   |                                                    |   |\n";
    cout << "|   |    WELCOME TO THE LIBRARY MANAGEMENT SYSTEM        |   |\n";
    cout << "|   |                                                    |   |\n";
    cout << "|   |    Developed by: Team Q (DSA Course Project)       |   |\n";
    cout << "|   |____________________________________________________|   |\n";
    cout << " \\__________________________________________________________/ \n";
    cout << "\n        [ Press Enter to Start the Application ]           \n";
    string dummy;
    getline(cin, dummy);
}

void ConsoleInterface::printHeader(const string &title) const
{
    clearScreen();
    cout << "       .--.                   .---.        \n";
    cout << "   .---|__|                   |___|---.    \n";
    cout << "   |---|--|                   |---|---|    \n";
    cout << "   |---|--|    LMS PROJECT    |---|---|    \n";
    cout << "   ^---^--^                   ^---^---^    \n";
    printDivider();
    cout << "|             LIBRARY MANAGEMENT SYSTEM (DSA)                |\n";
    printDivider();
    cout << "|  CATEGORY: " << title;
    // Pad with spaces to keep the border aligned
    int padding = 47 - (int)title.length();
    for (int i = 0; i < padding; ++i)
        cout << " ";
    cout << "|\n";
    printDivider();
}

void ConsoleInterface::waitForEnter() const
{
    cout << "\n >>> Press Enter to continue...";
    string dummy;
    getline(cin, dummy);
}

string ConsoleInterface::getInput(const string &prompt) const
{
    cout << " " << prompt;
    string input;
    getline(cin, input);
    return input;
}

void clearInput()
{
    cin.ignore('\n');
    cin.clear();
}

// --- Menus ---

void ConsoleInterface::printMainMenu() const
{
    printHeader("Main Menu");
    cout << "|                                                            |\n";
    cout << "|  1. [ Book Management ]                                    |\n";
    cout << "|  2. [ Patron Management ]                                  |\n";
    cout << "|  3. [ Transactions (Borrow/Return) ]                       |\n";
    cout << "|  4. [ Data Persistence (Save/Load) ]                       |\n";
    cout << "|                                                            |\n";
    cout << "|  0. [ Exit System ]                                        |\n";
    cout << "|                                                            |\n";
    printDivider();
}

void ConsoleInterface::run()
{
    printWelcomeBanner();
    while (running)
    {
        printMainMenu();
        cout << " Select an option: ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
            handleBookMenu();
        else if (choice == "2")
            handlePatronMenu();
        else if (choice == "3")
            handleTransactionMenu();
        else if (choice == "4")
            handleDataMenu();
        else if (choice == "0")
        {
            running = false;
            cout << "\n Thank you for using the Library Management System. Goodbye!\n";
        }
        else
        {
            cout << " [!] Invalid option. Please try again.\n";
            waitForEnter();
        }
    }
}

// --- Sub-Menus ---

void ConsoleInterface::handleBookMenu()
{
    // Delegate full book-related UI to BookMenu
    BookMenu menu(controller);
    menu.show();
}

void ConsoleInterface::handlePatronMenu()
{
    PatronMenu menu(controller);
    menu.show();
}

void ConsoleInterface::handleTransactionMenu()
{
    TransactionMenu menu(controller);
    menu.show();
}

void ConsoleInterface::handleDataMenu()
{
    bool back = false;
    while (!back)
    {
        printHeader("Data Persistence");
        cout << "|                                                            |\n";
        cout << "|  1. [ Save All Data ]                                      |\n";
        cout << "|  2. [ Load All Data ]                                      |\n";
        cout << "|                                                            |\n";
        cout << "|  0. [ Back to Main Menu ]                                  |\n";
        cout << "|                                                            |\n";
        printDivider();
        cout << " Select: ";

        string choice;
        getline(cin, choice);
        if (choice == "1")
            handleSaveData();
        else if (choice == "2")
            handleLoadData();
        else if (choice == "0")
            back = true;
        else
        {
            cout << " [!] Invalid option.\n";
            waitForEnter();
        }
    }
}

// Transaction history is handled in TransactionMenu.

void ConsoleInterface::handleSaveData()
{
    cout << "\n +-------------------------------------------------------+\n";
    cout << " | NOTICE: The [Save Data] feature is currently         |\n";
    cout << " | being implemented by Member 6.                        |\n";
    cout << " +-------------------------------------------------------+\n";
    waitForEnter();
}

void ConsoleInterface::handleLoadData()
{
    cout << "\n +-------------------------------------------------------+\n";
    cout << " | NOTICE: The [Load Data] feature is currently         |\n";
    cout << " | being implemented by Member 6.                        |\n";
    cout << " +-------------------------------------------------------+\n";
    waitForEnter();
}
