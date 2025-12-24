#pragma once
#include <string>
#include <iostream>
#include "dsa/Array.hpp"
using namespace std;

enum class PatronSearchKey { NAME, ID };
enum class PatronSortKey { NAME, MEMBERSHIP_DATE, BORROW_COUNT };

class Patron
{
private:
    string patronID;
    string name;
    string contact;
    string membershipDate;
    int borrowCount;
    bool borrowed;
public:
    Patron() = default;

    Patron(string patronID,
           string name,
           string contact,
           string membershipDate,
           int borrowCount = 0,
           bool borrowed = false)
    {
        this->patronID = patronID;
        this->name = name;
        this->contact = contact;
        this->membershipDate = membershipDate;
        this->borrowCount = borrowCount;
        this->borrowed = borrowed;
    }

    // for generic lookup
    const string getKey() { return patronID; }

    const string getID() { return patronID; }
    const string getName() { return name; }
    const string getContact() { return contact; }
    const string getMembershipDate() { return membershipDate; }
    int getBorrowCount() { return borrowCount; }
    bool isBorrowed() { return borrowed; }

    void setID(const string &id) { patronID = id; }
    void setName(const string &n) { name = n; }
    void setContact(const string &c) { contact = c; }
    void setMembershipDate(const string &date) { membershipDate = date; }
    void setBorrowCount(int bc) { borrowCount = bc; }
    void setBorrowed(bool b) { borrowed = b; }

    void incrementBorrowCount() { ++borrowCount; }

    string serialize();
    void deserialize(const string &line);
    
    Array<string> getFields();
    Array<string> getValues();
};
