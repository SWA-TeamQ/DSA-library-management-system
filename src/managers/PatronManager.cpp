#include "managers/PatronManager.hpp"
#include <algorithm>

void PatronManager::loadPatrons()
{
    store.loadData(patrons);
}

void PatronManager::savePatrons() const
{
    store.saveData(patrons);
}

void PatronManager::add(const Patron &p)
{
    patrons.push_back(p);
    store.addData(p);
}

void PatronManager::remove(const string &patronID)
{
    for (auto it = patrons.begin(); it != patrons.end(); ++it)
    {
        if (it != patrons.end())
        {
            patrons.erase(it);
            savePatrons(); // Save after removal
        }
    }
}

void PatronManager::displayAll() const
{
    for (const auto &patron : patrons)
    {
        patron.displayDetails();
    }
}
