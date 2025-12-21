#include "models/Patron.hpp"
#include <sstream>

using namespace std;

void Patron::displayDetails() const
{
    cout << "ID: " << patronID
         << " | Name: " << name
         << " | Contact: " << contact
         << " | Membership Date: " << membershipDate
         << " | Borrow Count: " << borrowCount << '\n';
}

string Patron::serialize() const
{
    return patronID + "," + name + "," + contact + "," + membershipDate + "," + to_string(borrowCount);
}

void Patron::deserialize(const string &line)
{
    stringstream ss(line);
    string field;

    getline(ss, patronID, ',');
    getline(ss, name, ',');
    getline(ss, contact, ',');
    getline(ss, membershipDate, ',');
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

vector<string> Patron::getFields() const
{
    return {"ID", "Name", "Contact", "Membership Date", "Borrow Count"};
}

vector<string> Patron::getValues() const
{
    return {patronID, name, contact, membershipDate, to_string(borrowCount)};
}