#include "models/Patron.hpp"
#include <sstream>
#include <iostream>
#include "dsa/Array.hpp"

using namespace std;

string Patron::serialize() const
{
    // Format: id,name,contact,membershipDate,borrowedFlag,activeCount,lifetimeCount
    return patronID + "," + name + "," + contact + "," + membershipDate + "," + (borrowed ? "1" : "0") + "," + to_string(activeBorrowCount) + "," + to_string(lifetimeBorrowCount);
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
    // active and lifetime borrow counts
    getline(ss, field, ',');
    if (!field.empty())
        activeBorrowCount = stoi(field);
    else
        activeBorrowCount = 0;

    getline(ss, field);
    if (!field.empty())
        lifetimeBorrowCount = stoi(field);
    else
        lifetimeBorrowCount = 0;
}

Array<string> Patron::getFields() const
{
    Array<string> fields;
    fields.append("ID");
    fields.append("Name");
    fields.append("Contact");
    fields.append("Membership Date");
    fields.append("Borrowed");
    fields.append("Active Borrows");
    fields.append("Borrow Count");
    return fields;
}

Array<string> Patron::getValues() const
{
    Array<string> values;
    values.append(patronID);
    values.append(name);
    values.append(contact);
    values.append(membershipDate);
    values.append(borrowed ? "borrowed" : "available");
    values.append(to_string(activeBorrowCount));
    values.append(to_string(lifetimeBorrowCount));
    return values;
}