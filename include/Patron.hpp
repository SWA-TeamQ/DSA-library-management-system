#pragma once
#include <string>
#include <iostream>
#include <chrono>
using namespace std;

class Patron {
private:
    string patronID;
    string name;
    string contact;
    chrono::system_clock::time_point membershipDate{chrono::system_clock::now()};
public:
    Patron() = default;
    Patron(string id, string n, string c)
        : patronID(move(id)), name(move(n)), contact(move(c)) {}

    const string& getID() const { return patronID; }
    const string& getName() const { return name; }
    const string& getContact() const { return contact; }
    chrono::system_clock::time_point getMembershipDate() const { return membershipDate; }

    void setName(const string& n) { name = n; }
    void setContact(const string& c) { contact = c; }

    void displayProfile(ostream& os = cout) const;
};
