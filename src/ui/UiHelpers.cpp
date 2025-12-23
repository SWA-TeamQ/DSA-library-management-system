#include "ui/UiHelpers.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"

using namespace std;

void print(const Book &book)
{
    const auto fields = book.getFields();
    const auto values = book.getValues();

    if(fields.size() != values.size()){
        cout << "Mismatching fields and values" << endl;
        return;
    }
    for(std::size_t i = 0; i < fields.size(); i++){
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(const Patron &patron){
    const auto fields = patron.getFields();
    const auto values = patron.getValues();

    if(fields.size() != values.size()){
        cout << "Mismatching fields and values" << endl;
        return;
    }
    for(int i = 0; i < fields.size(); i++){
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(const Transaction &transaction){
    const auto fields = transaction.getFields();
    const auto values = transaction.getValues();

    if(fields.size() != values.size()){
        cout << "Mismatching fields and values" << endl;
        return;
    }
    for(int i = 0; i < fields.size(); i++){
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void printAll(const Array<Book> books){
    Book temp = Book();

    Array<string> fields = temp.getFields();
    for(int i = 0; i < fields.size(); i++){
        for(int j = 0; j < fields.size() * 15; j++){
            cout << "-";
        }
        cout << setw(15) << fields[i];
        if( i != fields.size() - 1){
            cout << "|";
        }
        for(int j = 0; j < fields.size() * 15; j++){
            cout << "-";
        }
    }


}