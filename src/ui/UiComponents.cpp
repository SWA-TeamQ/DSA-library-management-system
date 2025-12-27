#include "ui/UiComponents.hpp"

void Row(Array<string> values, bool borderTop, int width)
{
    size_t totalWidth = values.size() * (width + 3) + 1;
    // border top
    if (borderTop)
    {
        cout << endl;
        cout << GRAY << string(totalWidth, '-') << RESET;
        cout << endl;
    }
    for (size_t i = 0; i < values.size(); i++)
    {
        cout << GRAY << "| " << RESET;
        cout << left << setw(width) << truncate(values[i], width) << " ";
    }
    cout << GRAY << "|" << RESET;
    cout << endl;

    // border bottom
    cout << GRAY << string(totalWidth, '-') << RESET;
    cout << endl;
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
