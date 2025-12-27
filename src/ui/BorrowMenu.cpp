#include "ui/BorrowMenu.hpp"

using namespace std;

void BorrowMenu::show()
{
    bool running = true;
    while (running)
    {
        printHeader("Borrow / Return");
        cout << "1. Borrow book\n"
             << "2. Return book\n"
             << "0. Back\n";

        int choice = readInt("Choose: ");

        switch (choice)
        {
        case 0:
            running = false;
            break;
        case 1:
            borrowBook();
            break;
        case 2:
            returnBook();
            break;
        default:
            cout << "Unknown choice.\n";
            break;
        }
    }
}

void BorrowMenu::borrowBook()
{
    printHeader("Borrow Book");
    Transaction t;
    Form<Transaction>(t, transactionSchema(), false); // gather bookID and patronID

    string patronId = t.getPatronID();
    string bookId = t.getBookID();

    if (controller.borrowBook(patronId, bookId))
        cout << "Borrowed.\n";
    else
        cout << "Borrow failed.\n";

    waitForEnter();
}

void BorrowMenu::returnBook()
{
    printHeader("Return Book");
    string patronId = readString("Patron ID: ");
    string bookId = readString("Book ISBN: ");

    if (controller.returnBook(patronId, bookId))
        cout << "Returned.\n";
    else
        cout << "Return failed.\n";

    waitForEnter();
}
