#include "managers/PatronManager.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

void PatronManager::loadPatrons()
{
    patronList.clear();
    patronTable.clear();
    if (!store.loadData(patronList))
    {
        cout << "Warning: Failed to load patrons from file\n";
        return;
    }
    buildSearchIndex();
}

void PatronManager::savePatrons()
{
    if (!store.saveData(patronList))
    {
        cout << "Warning: Failed to save patrons to file\n";
    }
}

void PatronManager::buildSearchIndex()
{
    patronTable.clear();
    for (int i = 0; i < (int)patronList.size(); i++)
    {
        patronTable.insert(patronList[i].getKey(), i);
    }
}

bool PatronManager::addPatron(const Patron &p)
{
    patronList.push_back(p);
    savePatrons();
    buildSearchIndex();
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
    int *indexPtr = patronTable.find(patronID);
    if (indexPtr)
    {
        return const_cast<Patron *>(&patronList[*indexPtr]);
    }
    return nullptr;
}

void PatronManager::sortPatrons(PatronSortKey key, bool reverse)
{
    // Implementation of sortPatrons using mergeSort (similar to BookManager)
    // Assuming mergeSort is available and works with Patron
    // For now, let's just leave it as a placeholder or implement if needed.
}

bool PatronManager::updatePatron(const string &patronID, const string &name, const string &contact, const string &membershipDate, int borrowCount)
{
    int *indexPtr = patronTable.find(patronID);
    if (!indexPtr) return false;

    Patron &p = patronList[*indexPtr];
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

void PatronManager::listAllPatrons() const
{
    cout << "\n--- All Patrons ---\n";
    if (patronList.empty())
    {
        cout << "No patrons found.\n";
        return;
    }
    for (const auto &p : patronList)
    {
        p.displayDetails();
        cout << "-----------------\n";
    }
}
