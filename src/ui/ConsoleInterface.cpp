#include "ui/ConsoleInterface.hpp"

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
    // printWelcomeBanner();
    while (running)
    {
        printMainMenu();
        int choice = readInt(" Select an option: ");
        switch (choice)
        {
        case 1:
            handleBookMenu();
            break;
        case 2:
            handlePatronMenu();
            break;
        case 3:
            handleTransactionMenu();
            break;
        case 4:
            handleDataMenu();
            break;
        case 0:
            running = false;
            cout << "\n Thank you for using the Library Management System. Goodbye!\n";
            break;
        default:
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
    cout<<"Saving Data ...\n";
    controller.save();
    cout<<"..........Done...............\n";
    waitForEnter();
}

void ConsoleInterface::handleLoadData()
{
    cout<<"Loading Data .... \n";
    controller.load();
    cout<<"...........Done...............\n";
    waitForEnter();
}
