#include "models/Patron.hpp"
#include <sstream>
#include <iostream>
#include "dsa/Array.hpp"

using namespace std;

string Patron::serialize() 
{
    // Format: id|name|contact|membershipDate|borrowedFlag|activeCount|lifetimeCount
    return patronID + "|" + name + "|" + contact + "|" + membershipDate + "|" + (borrowed ? "1" : "0") + "|" + to_string(activeBorrowCount) + "|" + to_string(lifetimeBorrowCount);
}

void Patron::deserialize(string line)
{
    stringstream ss(line);
    string field;

    getline(ss, patronID, '|');
    getline(ss, name, '|');
    getline(ss, contact, '|');
    getline(ss, membershipDate, '|');
    // borrowed flag
    getline(ss, field, '|');
    borrowed = (field == "1");
    // active and lifetime borrow counts
    getline(ss, field, '|');
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

static bool parseBool(const string &s)
{
    if (s == "1") return true;
    if (s == "0") return false;
    string t = s;
    for (auto &c : t) c = (char)tolower(c);
    return (t == "true" || t == "yes" || t == "y");
}

string Patron::getField(const string &key)
{
    if (key == "id") return patronID;
    if (key == "name") return name;
    if (key == "contact") return contact;
    if (key == "membershipDate") return membershipDate;
    if (key == "activeBorrowCount") return to_string(activeBorrowCount);
    if (key == "borrowCount") return to_string(lifetimeBorrowCount);
    if (key == "borrowed") return borrowed ? string("1") : string("0");
    return string();
}

bool Patron::setField(const string &key, const string &value)
{
    try
    {
        if (key == "id") { patronID = value; return true; }
        if (key == "name") { name = value; return true; }
        if (key == "contact") { contact = value; return true; }
        if (key == "membershipDate") { membershipDate = value; return true; }
        if (key == "activeBorrowCount") { activeBorrowCount = stoi(value); if (activeBorrowCount < 0) activeBorrowCount = 0; return true; }
        if (key == "borrowCount") { lifetimeBorrowCount = stoi(value); if (lifetimeBorrowCount < 0) lifetimeBorrowCount = 0; return true; }
        if (key == "borrowed") { borrowed = parseBool(value); return true; }
    }
    catch (...) { return false; }
    return false;
}

Array<string> Patron::getFields() 
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

Array<string> Patron::getValues() 
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
