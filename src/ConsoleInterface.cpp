#include "ConsoleInterface.hpp"
#include <iostream>
#include <cstdlib> // for system()
using namespace std;

// --- UI Helpers ---

void ConsoleInterface::clearScreen() const
{
    // Simple clear screen for Windows.
    // For cross-platform, we might use preprocessor directives.
    system("cls");
}

void ConsoleInterface::printDivider() const
{
    cout << "============================================================\n";
}

void ConsoleInterface::printHeader(const string &title) const
{
    clearScreen();
    printDivider();
    cout << "      📚  LIBRARY MANAGEMENT SYSTEM  📚\n";
    printDivider();
    cout << " :: " << title << " ::\n";
    printDivider();
}

void ConsoleInterface::waitForEnter() const
{
    cout << "\n[Press Enter to continue...]";
    cin.ignore(10000, '\n'); // Clear buffer if needed
    // In some cases, if buffer is empty, this might wait.
    // If buffer has newline, it skips.
    // A simple getline is safer for "pause".
    string dummy;
    getline(cin, dummy);
}

string ConsoleInterface::getInput(const string &prompt) const
{
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

// --- Menus ---

void ConsoleInterface::printMainMenu() const
{
    printHeader("Main Menu");
    cout << " 1. 📖 Book Management\n";
    cout << " 2. 👤 Member Management\n";
    cout << " 3. 🔄 Transactions (Borrow/Return)\n";
    cout << " 4. 💾 Data Persistence (Save/Load)\n";
    cout << " 0. 🚪 Exit\n";
    printDivider();
    cout << " Select an option: ";
}

void ConsoleInterface::run()
{
    while (running)
    {
        printMainMenu();
        string choice;
        getline(cin, choice);

        if (choice == "1")
            handleBookMenu();
        else if (choice == "2")
            handleMemberMenu();
        else if (choice == "3")
            handleTransactionMenu();
        else if (choice == "4")
            handleDataMenu();
        else if (choice == "0")
        {
            running = false;
            cout << "\nGoodbye! 👋\n";
        }
        else
        {
            cout << "Invalid option. Please try again.\n";
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
        cout << " 1. Add New Book\n";
        cout << " 2. List All Books\n";
        cout << " 3. Search Books (Title/Author) [Coming Soon]\n";
        cout << " 4. Sort Books [Coming Soon]\n";
        cout << " 5. Remove Book [Coming Soon]\n";
        cout << " 0. Back to Main Menu\n";
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
            cout << "Invalid option.\n";
            waitForEnter();
        }
    }
}

void ConsoleInterface::handleMemberMenu()
{
    bool back = false;
    while (!back)
    {
        printHeader("Member Management");
        cout << " 1. Register New Member\n";
        cout << " 2. List All Members\n";
        cout << " 3. Search Member [Coming Soon]\n";
        cout << " 4. Remove Member [Coming Soon]\n";
        cout << " 0. Back to Main Menu\n";
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
            cout << "Invalid option.\n";
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
        cout << " 1. Borrow Book\n";
        cout << " 2. Return Book\n";
        cout << " 3. View Borrow History [Coming Soon]\n";
        cout << " 0. Back to Main Menu\n";
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
            cout << "Invalid option.\n";
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
        cout << " 1. Save All Data [Coming Soon]\n";
        cout << " 2. Load All Data [Coming Soon]\n";
        cout << " 0. Back to Main Menu\n";
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
            cout << "Invalid option.\n";
            waitForEnter();
        }
    }
}

// --- Implementation of Operations ---

void ConsoleInterface::handleAddBook()
{
    printHeader("Add New Book");
    string title = getInput(" Enter Title: ");
    string author = getInput(" Enter Author: ");
    string isbn = getInput(" Enter ISBN: ");
    string category = getInput(" Enter Category: ");

    if (title.empty() || author.empty() || isbn.empty())
    {
        cout << "\n ❌ Error: Title, Author and ISBN are required.\n";
    }
    else
    {
        bool ok = controller.addBook(Book(title, author, isbn, category));
        if (ok)
            cout << "\n ✅ Book added successfully!\n";
        else
            cout << "\n ❌ Error: Book with this ISBN already exists.\n";
    }
    waitForEnter();
}

void ConsoleInterface::handleListBooks()
{
    printHeader("Library Catalog");
    controller.listAllBooks();
}

void ConsoleInterface::handleAddPatron()
{
    printHeader("Register New Member");
    string id = getInput(" Enter Member ID: ");
    string name = getInput(" Enter Name: ");
    string contact = getInput(" Enter Contact Info: ");

    if (id.empty() || name.empty())
    {
        cout << "\n ❌ Error: ID and Name are required.\n";
    }
    else
    {
        bool ok = controller.addPatron(Patron(id, name, contact));
        if (ok)
            cout << "\n ✅ Member registered successfully!\n";
        else
            cout << "\n ❌ Error: Member with this ID already exists.\n";
    }
    waitForEnter();
}

void ConsoleInterface::handleListPatrons()
{
    printHeader("Registered Members");
    controller.listAllPatrons();
}

void ConsoleInterface::handleBorrow()
{
    printHeader("Borrow Book");
    string pid = getInput(" Enter Member ID: ");
    string isbn = getInput(" Enter Book ISBN: ");

    if (controller.borrowBook(pid, isbn))
    {
        cout << "\n ✅ Borrow successful! Due date is in 14 days.\n";
    }
    else
    {
        cout << "\n ❌ Borrow failed. Check if book exists, is available, or member ID is valid.\n";
    }
}

void ConsoleInterface::handleReturn()
{
    printHeader("Return Book");
    string pid = getInput(" Enter Member ID: ");
    string isbn = getInput(" Enter Book ISBN: ");

    if (controller.returnBook(pid, isbn))
    {
        cout << "\n ✅ Return processed successfully.\n";
    }
    else
    {
        cout << "\n ❌ Return failed. Check details.\n";
    }
}

// --- Placeholders for Future Features ---

void ConsoleInterface::handleSearchBooks()
{
    cout << "\n 🚧 Feature [Search Books] is assigned to Member 2.\n";
    waitForEnter();
}

void ConsoleInterface::handleSortBooks()
{
    cout << "\n 🚧 Feature [Sort Books] is assigned to Member 2.\n";
    waitForEnter();
}

void ConsoleInterface::handleRemoveBook()
{
    cout << "\n 🚧 Feature [Remove Book] is assigned to Member 2.\n";
    waitForEnter();
}

void ConsoleInterface::handleSearchPatrons()
{
    cout << "\n 🚧 Feature [Search Member] is assigned to Member 3.\n";
    waitForEnter();
}

void ConsoleInterface::handleRemovePatron()
{
    cout << "\n 🚧 Feature [Remove Member] is assigned to Member 3.\n";
    waitForEnter();
}

void ConsoleInterface::handleViewHistory()
{
    cout << "\n 🚧 Feature [View History] is assigned to Member 4.\n";
    waitForEnter();
}

void ConsoleInterface::handleSaveData()
{
    cout << "\n 🚧 Feature [Save Data] is assigned to Member 6.\n";
    waitForEnter();
}

void ConsoleInterface::handleLoadData()
{
    cout << "\n 🚧 Feature [Load Data] is assigned to Member 6.\n";
    waitForEnter();
}
