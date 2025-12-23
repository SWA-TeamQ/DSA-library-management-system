#include "ui/UiHelpers.hpp"

void clearInput()
{
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

void waitForEnter()
{
    string dummy;
    clearInput();
    getline(cin, dummy);
}

string getString(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int getInt(const string &prompt)
{
    int input;
    bool valid = true;
    do
    {
        valid = true;
        cout << prompt;
        cin >> input;
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a valid integer." << endl;
            clearInput();
            valid = false;
        }
        else
        {
            clearInput();
            return input;
        }
    } while (valid);
}

void clearScreen()
{
    system("cls");
}

void printDivider()
{
    cout << "+------------------------------------------------------------+\n";
}

void printWelcomeBanner()
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
    waitForEnter();
}

void printHeader(const string &title)
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

/**
 * print (overloaded) - to print the details of the object
 * tablePrint (overloaded) - to print the list of objects in a table view
 */

void print(const Book &book)
{
    const auto fields = book.getFields();
    const auto values = book.getValues();

    for (int i = 0; i < fields.size(); i++)
    {
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(const Patron &patron)
{
    const auto fields = patron.getFields();
    const auto values = patron.getValues();

    for (int i = 0; i < fields.size(); i++)
    {
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(const Transaction &transaction)
{
    const auto fields = transaction.getFields();
    const auto values = transaction.getValues();

    for (int i = 0; i < fields.size(); i++)
    {
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void tablePrint(const Array<Book> &books)
{
    Book temp = Book();
    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (const auto &book : books)
    {
        Row(book.getValues());
    }
}

void tablePrint(const Array<Patron> &patrons)
{
    Patron temp = Patron();

    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (const auto &book : patrons)
    {
        Row(book.getValues());
    }
}

void tablePrint(const Array<Transaction> &transactions)
{
    Transaction temp = Transaction();

    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (const auto &transaction : transactions)
    {
        Row(transaction.getValues());
    }
}