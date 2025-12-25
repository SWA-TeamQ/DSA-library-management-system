#include "models/Patron.hpp"
#include <sstream>
#include <iostream>
#include "dsa/Array.hpp"

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

Array<string> Patron::getFields() 
{
    Array<string> fields;
    fields.append("ID");
    fields.append("Name");
    fields.append("Contact");
    fields.append("Membership Date");
    fields.append("Borrowed");
    fields.append("Borrow Count");
    return fields;
}

Array<string> Patron::getValues() 
{
    Array<string> values;
    values.append(patronID);
    values.append(name);
    values.append(contact);
    values.append(membershipDate);
    values.append(borrowed ? "borrowed" : "available");
    values.append(to_string(borrowCount));
    return values;
}