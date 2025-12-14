#include "managers/PatronManager.hpp"
#include <algorithm>

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

bool PatronManager::removePatron(const string &patronID)
{
    patrons.erase(patronID);
    auto it = std::find_if(patronList.begin(), patronList.end(), [&](const Patron &pat)
                           { return pat.getID() == patronID; });
    if (it != patronList.end())
        patronList.erase(it);
    savePatrons(); // persist after removal
    return true;
}

Patron *PatronManager::findPatron(const string &patronID)
{
    return patrons.find(patronID);
}

void PatronManager::displayAll() const
{
    cout << "--- Patrons ---\n";
    for (auto *p : patrons.all())
        p->displayDetails();
}
// findpatronbyname
Patron* PatronManager::findPatronByName(const string& name)
{
    for (auto& p : patronList)
    {
        if (p.getName() == name)
            return &p;
    }
    return nullptr;
}
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
