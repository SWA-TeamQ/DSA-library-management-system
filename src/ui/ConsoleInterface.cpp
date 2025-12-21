#include "ui/ConsoleInterface.hpp"
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
    for (int i = 0; i < padding; ++i) cout << " ";
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

void clearInput(){
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
    cout << " Select an option: ";
}

void ConsoleInterface::run()
{
    printWelcomeBanner();
    while (running)
    {
        printMainMenu();
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
    bool back = false;
    while (!back)
    {
        printHeader("Book Management");
        cout << "|                                                            |\n";
        cout << "|  1. [ Add New Book ]                                       |\n";
        cout << "|  2. [ List All Books ]                                     |\n";
        cout << "|  3. [ Search Books (Title/Author) ]                        |\n";
        cout << "|  4. [ Sort Books ]                                         |\n";
        cout << "|  5. [ Remove Book ]                                        |\n";
        cout << "|                                                            |\n";
        cout << "|  0. [ Back to Main Menu ]                                  |\n";
        cout << "|                                                            |\n";
        printDivider();
        cout << " Select: ";

        string choice;
        getline(cin, choice);
        if (choice == "1")
            handleAddBook();
        else if (choice == "2")
        {
            handleListBooks();
            waitForEnter();
        }
        else if (choice == "3")
            handleSearchBooks();
        else if (choice == "4")
            handleSortBooks();
        else if (choice == "5")
            handleRemoveBook();
        else if (choice == "0")
            back = true;
        else
        {
            cout << " [!] Invalid option.\n";
            waitForEnter();
        }
    }
}

void ConsoleInterface::handlePatronMenu()
{
    bool back = false;
    while (!back)
    {
        printHeader("Patron Management");
        cout << "|                                                            |\n";
        cout << "|  1. [ Register New Patron ]                                |\n";
        cout << "|  2. [ List All Members ]                                   |\n";
        cout << "|  3. [ Search Patron ]                                      |\n";
        cout << "|  4. [ Remove Patron ]                                      |\n";
        cout << "|                                                            |\n";
        cout << "|  0. [ Back to Main Menu ]                                  |\n";
        cout << "|                                                            |\n";
        printDivider();
        cout << " Select: ";

        string choice;
        getline(cin, choice);
        if (choice == "1")
            handleAddPatron();
        else if (choice == "2")
        {
            handleListPatrons();
            waitForEnter();
        }
        else if (choice == "3")
            handleSearchPatrons();
        else if (choice == "4")
            handleRemovePatron();
        else if (choice == "0")
            back = true;
        else
        {
            cout << " [!] Invalid option.\n";
            waitForEnter();
        }
    }
}

void ConsoleInterface::handleTransactionMenu()
{
    bool back = false;
    while (!back)
    {
        printHeader("Transactions");
        cout << "|                                                            |\n";
        cout << "|  1. [ Borrow Book ]                                        |\n";
        cout << "|  2. [ Return Book ]                                        |\n";
        cout << "|  3. [ View Borrow History ]                                |\n";
        cout << "|                                                            |\n";
        cout << "|  0. [ Back to Main Menu ]                                  |\n";
        cout << "|                                                            |\n";
        printDivider();
        cout << " Select: ";

        string choice;
        getline(cin, choice);
        if (choice == "1")
        {
            handleBorrow();
            waitForEnter();
        }
        else if (choice == "2")
        {
            handleReturn();
            waitForEnter();
        }
        else if (choice == "3")
            handleViewHistory();
        else if (choice == "0")
            back = true;
        else
        {
            cout << " [!] Invalid option.\n";
            waitForEnter();
        }
    }
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

void ConsoleInterface::handleAddBook()
{
    printHeader("Add New Book");
    string title = getInput(" Enter Title: ");
    string author = getInput(" Enter Author: ");
    string isbn = getInput(" Enter ISBN: ");
    string edition = getInput(" Enter Edition: ");
    string category = getInput(" Enter Category: ");

    if (title.empty() || author.empty() || isbn.empty())
    {
        cout << "\n Error: Title, Author and ISBN are required.\n";
    }
    else
    {
        bool ok = controller.addBook(Book(title, author, isbn, edition, 2023, category));
        if (ok)
            cout << "\n Book added successfully!\n";
        else
            cout << "\n Error: Book with this ISBN already exists.\n";
    }
    waitForEnter();
}

void ConsoleInterface::handleListBooks()
{
    printHeader("Library Catalog");
    cout << "\n [ Listing all books in the database ]\n";
    cout << " ------------------------------------------------------------\n";
    controller.listAllBooks();
    cout << " ------------------------------------------------------------\n";
    cout << " [ End of Catalog ]\n";
}

void ConsoleInterface::handleAddPatron()
{
    printHeader("Register New Patron");
    string id = getInput(" Enter Patron ID: ");
    string name = getInput(" Enter Name: ");
    string contact = getInput(" Enter Contact Info: ");

    if (id.empty() || name.empty())
    {
        cout << "\n Error: ID and Name are required.\n";
    }
    else
    {
        bool ok = controller.addPatron(Patron(id, name, contact, "Regular", 0));
        if (ok)
            cout << "\n Patron registered successfully!\n";
        else
            cout << "\n Error: Patron with this ID already exists.\n";
    }
    waitForEnter();
}

void ConsoleInterface::handleListPatrons()
{
    printHeader("Registered Members");
    cout << "\n [ Listing all registered patrons ]\n";
    cout << " ------------------------------------------------------------\n";
    controller.listAllPatrons();
    cout << " ------------------------------------------------------------\n";
    cout << " [ End of List ]\n";
}

void ConsoleInterface::handleBorrow()
{
    string pid = getInput("Patron ID: ");
    string isbn = getInput("Book ISBN: ");

    if (controller.borrowBook(pid, isbn))
        cout << "Borrow successful. Due in 14 days.\n";
    else
        cout << "Borrow failed." << "\n";
}


void ConsoleInterface::handleReturn()
{
    string pid = getInput("Patron ID: ");
    string isbn = getInput("Book ISBN: ");

    if (controller.returnBook(pid, isbn))
    {
        cout << "Return successful.\n";
    }
    else
        cout << "Return failed.\n";
}


// --- Placeholders for Future Features ---

void ConsoleInterface::handleSearchBooks()
{
    cout << "\n +-------------------------------------------------------+\n";
    cout << " | NOTICE: The [Search Books] feature is currently       |\n";
    cout << " | being implemented by Member 2.                        |\n";
    cout << " +-------------------------------------------------------+\n";
    waitForEnter();
}

void ConsoleInterface::handleSortBooks()
{
    cout << "\n +-------------------------------------------------------+\n";
    cout << " | NOTICE: The [Sort Books] feature is currently         |\n";
    cout << " | being implemented by Member 2.                        |\n";
    cout << " +-------------------------------------------------------+\n";
    waitForEnter();
}

void ConsoleInterface::handleRemoveBook()
{
    cout << "\n +-------------------------------------------------------+\n";
    cout << " | NOTICE: The [Remove Book] feature is currently        |\n";
    cout << " | being implemented by Member 2.                        |\n";
    cout << " +-------------------------------------------------------+\n";
    waitForEnter();
}

void ConsoleInterface::handleSearchPatrons()
{
    cout << "\n +-------------------------------------------------------+\n";
    cout << " | NOTICE: The [Search Patron] feature is currently      |\n";
    cout << " | being implemented by Member 3.                        |\n";
    cout << " +-------------------------------------------------------+\n";
    waitForEnter();
}

void ConsoleInterface::handleRemovePatron()
{
    cout << "\n +-------------------------------------------------------+\n";
    cout << " | NOTICE: The [Remove Patron] feature is currently      |\n";
    cout << " | being implemented by Member 3.                        |\n";
    cout << " +-------------------------------------------------------+\n";
    waitForEnter();
}

void ConsoleInterface::handleViewHistory()
{
    cout << "\n Feature [View History] is assigned to Patron 4.\n";
    waitForEnter();
}


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
