#include "models/Patron.hpp"
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

string Patron::serialize() const
{
    return patronID + "," + name + "," + contact + "," + membershipDate + "," + (borrowed ? "1" : "0") + "," + to_string(borrowCount);
}

void Patron::deserialize(const string &line)
{
    stringstream ss(line);
    string field;

    getline(ss, patronID, ',');
    getline(ss, name, ',');
    getline(ss, contact, ',');
    getline(ss, membershipDate, ',');
    // borrowed flag
    getline(ss, field, ',');
    borrowed = (field == "1");
    // borrow count (lifetime)
    getline(ss, field);
    if (!field.empty())
    {
        borrowCount = stoi(field);
    }
    else
    {
        borrowCount = 0;
    }
}

Array<string> Patron::getFields() const
{
    return {
        "ID", 
        "Name", 
        "Contact", 
        "Membership Date", 
        "Borrowed", 
        "Borrow Count"};
}

    Array<string> Patron::getValues() const
{
    return {
        patronID, 
        name, 
        contact, 
        membershipDate, 
        borrowed ? "borrowed" : "available", 
        to_string(borrowCount)};
}