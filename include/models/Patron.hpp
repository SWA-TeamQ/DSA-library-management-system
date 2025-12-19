#pragma once
#include <string>
#include <iostream>
using namespace std;

class Patron
{
private:
    string patronID;
    string name;
    string contact;
    string membershipDate;
    int borrowCount{0};

public:
    Patron() = default;

    Patron(string patronID,
           string name,
           string contact,
           string membershipDate,
           int borrowCount = 0)
    {
        this->patronID = patronID;
        this->name = name;
        this->contact = contact;
        this->membershipDate = membershipDate;
        this->borrowCount = borrowCount;
    }


    // for generic lookup
    const string &getKey() const { return patronID; }

    const string &getID() const { return patronID; }
    const string &getName() const { return name; }
    const string &getContact() const { return contact; }
    const string &getMembershipDate() const { return membershipDate; }
    int getBorrowCount() const { return borrowCount; }

    void setID(const string &id) { patronID = id; }
    void setName(const string &n) { name = n; }
    void setContact(const string &c) { contact = c; }
    void setMembershipDate(const string &date) { membershipDate = date; }
    void setBorrowCount(int bc) { borrowCount = bc; }

    void incrementBorrowCount() { ++borrowCount; }
    void decrementBorrowCount()
    {
        if (borrowCount > 0)
            --borrowCount;
    }

    void displayDetails() const;
    string serialize() const;
    void deserialize(const string &line);
};
