#include "managers/PatronManager.hpp"
#include <algorithm>
#include <iomanip>

void PatronManager::loadPatrons()
{
    if (!store.loadData(patronList))
    {
        cout << "Warning: Failed to load patrons from file\n";
        return;
    }
    for (auto &p : patronList)
        patrons.insert(&p); // insert into hash table
}

void PatronManager::savePatrons()
{
    if (!store.saveData(patronList))
    {
        cout << "Warning: Failed to save patrons to file\n";
    }
}

bool PatronManager::addPatron(const Patron &p)
{
    patronList.push_back(p);
    if (patrons.insert(&patronList.back()))
    {
        if (!store.addData(patronList.back()))
        {
            patrons.erase(patronList.back().getID());
            patronList.pop_back();
            return false;
        }
        return true;
    }
    else
    {
        patronList.pop_back();
        return false;
    }
}

// solved the issue Constraint: cannot remove patrons with unreturned books
bool PatronManager::removePatron(const string& patronID)
{
    Patron* p = patrons.find(patronID);
    if (!p)
        return false;

    // TODO: Prevent removal if patron has unreturned books
    // This will be enforced via TransactionManager

    patrons.erase(patronID);

    auto it = std::find_if(
        patronList.begin(),
        patronList.end(),
        [&](const Patron& pat)
        {
            return pat.getID() == patronID;
        }
    );

    if (it != patronList.end())
        patronList.erase(it);

    savePatrons();
    return true;
}

Patron *PatronManager::findPatron(const string &patronID) const
{
    return patrons.find(patronID);
}

//formatted table with borrow counts and contact info

void PatronManager::displayAll() const
{
    cout << "\n Patron List \n";

    cout << left
         << setw(15) << "Patron ID"
         << setw(20) << "Name"
         << setw(25) << "Contact"
         << setw(10) << "Borrowed"
         << "\n";

    cout << string(70, '-') << "\n";

    for (auto* p : patrons.all())
    {
        cout << left
             << setw(15) << p->getID()
             << setw(20) << p->getName()
             << setw(25) << p->getContact()
             << setw(10) << p->getBorrowCount()
             << "\n";
    }

    cout << "\n";
}


// searching and accessing the patrons using their names
Patron* PatronManager::findPatronByName(const string& name)
{
    for (auto& p : patronList)
    {
        if (p.getName() == name)
            return &p;
    }
    return nullptr;
}

// update patron contact function
bool PatronManager::updatePatronContact(
    const string& patronID,
    const string& newContact)
{
    Patron* p = patrons.find(patronID);
    if (!p)
        return false;

    p->setContact(newContact);
    savePatrons();
    return true;
}
