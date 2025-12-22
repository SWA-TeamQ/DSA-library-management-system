#include "ui/UiHelpers.hpp"
#include <iostream>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include <vector>

using namespace std;

void print(const Book &book)
{
    vector<string> &fields = book.getFields();
    vector<string> &values = book.getValues();

    if(fields.size() != values.size()){
        cout << "Mismatching fields and values" << endl;
        return;
    }
    for(int i = 0; i < fields.size(); i++){
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}

void print(const Patron &patron){
    vector<string> &fields = patron.getFields();
    vector<string> &values = patron.getValues();

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
    vector<string> &fields = transaction.getFields();
    vector<string> &values = transaction.getValues();

    if(fields.size() != values.size()){
        cout << "Mismatching fields and values" << endl;
        return;
    }
    for(int i = 0; i < fields.size(); i++){
        cout << '\t' << fields[i] << ": " << values[i] << endl;
    }
    cout << endl;
}
