#include "ui/UiHelpers.hpp"

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover input
}

void waitForEnter()
{
    cout << "Press Enter to continue...";
    if (cin.peek() != '\n')
    {
        clearInput();
    }
    cin.get();
}

string readString(string prompt, bool optional, string fallback)
{
    string input = fallback;
    do
    {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        if (!optional && input.empty())
        {
            cout << "This field is required " << endl;
        }
    } while (!optional && input.empty());
    return input;
}

int readInt(const string &prompt, bool optional, int fallback)
{
    string input;
    int number = fallback;
    bool valid;

    do
    {
        valid = true;
        cout << prompt;

        getline(cin, input);

        if (input.empty())
        {
            if (!optional)
            {
                cout << "This field is required" << endl;
                valid = false;
            }
            else
            {
                return number;
            }
        }
        else
        {
            try
            {
                number = stoi(input);
            }
            catch (...)
            {
                cout << "Invalid number. Try again." << endl;
                valid = false;
            }
        }
    } while (!valid);

    return number;
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

void printHeader(string title)
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
    int padding = 46 - (int)title.length();
    for (int i = 0; i < padding; ++i)
        cout << " ";
    cout << "|\n";
    printDivider();
}

/**
 * print (overloaded) - to print the details of the object
 * tablePrint (overloaded) - to print the list of objects in a table view
 */

void print(Book &book)
{
    auto fields = book.getFields();
    auto values = book.getValues();

    cout << endl;
    for (size_t i = 0; i < fields.size(); i++)
    {
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(Patron &patron)
{
    auto fields = patron.getFields();
    auto values = patron.getValues();

    cout << endl;
    for (size_t i = 0; i < fields.size(); i++)
    {
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(Transaction &transaction)
{
    auto fields = transaction.getFields();
    auto values = transaction.getValues();

    cout << endl;
    for (size_t i = 0; i < fields.size(); i++)
    {
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void tablePrint(Array<Book> &books)
{
    Book temp = Book();
    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (auto &book : books)
    {
        Row(book.getValues());
    }
}

void tablePrint(Array<Book *> &books)
{
    Book temp = Book();
    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (auto *book : books)
    {
        Row((*book).getValues());
    }
}

void tablePrint(Array<Patron> &patrons)
{
    Patron temp = Patron();

    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (auto &patron : patrons)
    {
        Row(patron.getValues());
    }
}

void tablePrint(Array<Patron *> &patrons)
{
    Patron temp = Patron();

    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (auto *patron : patrons)
    {
        Row((*patron).getValues());
    }
}

void tablePrint(Array<Transaction> &transactions)
{
    Transaction temp = Transaction();

    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (auto &transaction : transactions)
    {
        Row(transaction.getValues());
    }
}

void tablePrint(Array<Transaction *> &transactions)
{
    Transaction temp = Transaction();

    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for (auto *transaction : transactions)
    {
        Row((*transaction).getValues());
    }
}