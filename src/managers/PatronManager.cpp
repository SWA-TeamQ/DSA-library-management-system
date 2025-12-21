#include "managers/PatronManager.hpp"
#include <algorithm>
#include <iostream>

using namespace std;


bool PatronManager::addPatron(const Patron &p)
{
    patronList.push_back(p);
    patronTable.insert()
    patronsStore.addData(p);
    return true;
}

bool PatronManager::removePatron(const string &patronID)
{
    int *indexPtr = patronTable.find(patronID);
    if (indexPtr)
    {
        int index = *indexPtr;
        patronList.erase(patronList.begin() + index);
        savePatrons();
        buildSearchIndex();
        return true;
    }
    return false;
}

Patron *PatronManager::findPatron(const string &patronID) const
{
    auto it = patronTable.find(patronID);
    if(it != patronTable.end()){
        return &it->second;
    }
    return nullptr;
}

void PatronManager::sortPatrons(const PatronSortKey &key, bool reverse)
{

}

bool PatronManager::updatePatron(const Patron &p)
{
    auto it = patronTable.find(p.getKey());
    if(it != patronTable.end()){
        patronList[it->second] = p;
        savePatrons();
        return true;
    }
    return false;
}

    bool changed = false;

    if (!name.empty() && p.getName() != name) { p.setName(name); changed = true; }
    if (!contact.empty() && p.getContact() != contact) { p.setContact(contact); changed = true; }
    if (!membershipDate.empty() && p.getMembershipDate() != membershipDate) { p.setMembershipDate(membershipDate); changed = true; }
    if (p.getBorrowCount() != borrowCount) { p.setBorrowCount(borrowCount); changed = true; }

    if (changed)
    {
        savePatrons();
    }
    return true;
}
