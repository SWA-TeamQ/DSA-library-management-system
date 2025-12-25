#pragma once
#include <string>
#include <iostream>
#include "dsa/Array.hpp"
using namespace std;

enum class PatronSearchKey
{
    NAME,
    ID
};
enum class PatronSortKey
{
    NAME,
    MEMBERSHIP_DATE,
    BORROW_COUNT
};

class Patron
{
private:
    string patronID;
    string name;
    string contact;
    string membershipDate;
    int activeBorrowCount{0};
    int lifetimeBorrowCount{0};
    bool borrowed{false};

public:
    Patron() = default;

    Patron(string patronID,
           string name,
           string contact,
           string membershipDate,
           int lifetimeBorrowCount = 0,
           int activeBorrowCount = 0,
           bool borrowed = false)
    {
        this->patronID = patronID;
        this->name = name;
        this->contact = contact;
        this->membershipDate = membershipDate;
        this->activeBorrowCount = activeBorrowCount;
        this->lifetimeBorrowCount = lifetimeBorrowCount;
        this->borrowed = borrowed;
    }

    // for generic lookup
    string &getKey() { return patronID; }

    string &getID() { return patronID; }
    string &getName() { return name; }
    string &getContact() { return contact; }
    string &getMembershipDate() { return membershipDate; }
    int getBorrowCount() { return lifetimeBorrowCount; }
    bool isBorrowed() { return borrowed; }

    // lifetime borrow count (total times patron borrowed any book)
    // active borrow count (currently checked-out items)
    int getActiveBorrowCount() { return activeBorrowCount; }

    void setID(const string &id) { patronID = id; }
    void setName(const string &n) { name = n; }
    void setContact(const string &c) { contact = c; }
    void setMembershipDate(const string &date) { membershipDate = date; }
    void setBorrowCount(int bc) { lifetimeBorrowCount = bc; }
    void setActiveBorrowCount(int bc) { activeBorrowCount = bc; }
    void setBorrowed(bool b) { borrowed = b; }

    void incrementBorrowCount() { ++lifetimeBorrowCount; }
    void incrementActiveBorrowCount() { ++activeBorrowCount; }
    void decrementActiveBorrowCount()
    {
        if (activeBorrowCount > 0)
            --activeBorrowCount;
    }

    string serialize() const;
    void deserialize(const string &line);

    Array<string> getFields();
    Array<string> getValues();
};
