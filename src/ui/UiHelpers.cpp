#include "ui/UiHelpers.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "UiComponents.cpp"

using namespace std;

/**
 * print (overloaded) - to print the details of the object
 * tablePrint (overloaded) - to print the list of objects in a table view
 */

void print(const Book &book)
{
    const auto fields = book.getFields();
    const auto values = book.getValues();

    for(int i = 0; i < fields.size(); i++){
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(const Patron &patron){
    const auto fields = patron.getFields();
    const auto values = patron.getValues();

    for(int i = 0; i < fields.size(); i++){
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(const Transaction &transaction){
    const auto fields = transaction.getFields();
    const auto values = transaction.getValues();

    for(int i = 0; i < fields.size(); i++){
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void tablePrint(const Array<Book> &books){
    Book temp = Book();
    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for(const auto &book: books){
        Row(book.getValues());
    }

}

void tablePrint(const Array<Patron> &patrons){
    Patron temp = Patron();

    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for(const auto &book: patrons){
        Row(book.getValues());
    }
}

void tablePrint(const Array<Transaction> &transactions){
    Transaction temp = Transaction();

    // table header
    Array<string> fields = temp.getFields();
    Row(fields, true); // true for the top border

    // table rows
    for(const auto &transaction: transactions){
        Row(transaction.getValues());
    }
}