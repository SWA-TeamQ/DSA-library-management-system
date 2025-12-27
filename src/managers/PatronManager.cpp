#include "managers/PatronManager.hpp"

using namespace std;

bool PatronManager::addPatron(Patron &p)
{
    patronTable[p.getKey()] = p;
    searchMap.insert(p);
    patronStore.addData(p);
    return true;
}

bool PatronManager::removePatron(PatronSearchKey key, string value)
{
    Array<string> ids;
    switch (key)
    {
    case PatronSearchKey::ID:
        ids.append(value);
        break;
    case PatronSearchKey::NAME:
        ids = searchMap.findByName(value);
        break;
    }

    if (ids.empty())
    {
        return false;
    }

    bool deleted = false;
    for (auto &id : ids)
    {
        Patron *p = patronTable.find(id);
        if (!p)
            continue;

        // Prevent deletion if patron still has an active borrow
        if (p->isBorrowed())
        {
            cout << "Patron " << p->getKey() << " has active borrows and cannot be removed" << endl;
            continue;
        }

        deleted = true;
        searchMap.remove(*p);
        patronTable.remove(id);
    }

    if (deleted)
    {
        savePatrons();
    }
    return deleted;
}

Patron *PatronManager::findPatron(PatronSearchKey key, string value)
{
    Array<string> ids;
    switch (key)
    {
    case PatronSearchKey::ID:
        ids.append(value);
        break;
    case PatronSearchKey::NAME:
        ids = searchMap.findByName(value);
        break;
    }

    if (ids.empty())
    {
        return nullptr;
    }

    return patronTable.find(ids[0]);
}

Array<Patron *> PatronManager::findPatrons(PatronSearchKey key, string value)
{
    Array<string> ids;
    switch (key)
    {
    case PatronSearchKey::ID:
        ids.append(value);
        break;
    case PatronSearchKey::NAME:
        ids = searchMap.findByName(value);
        break;
    }

    Array<Patron *> patrons;
    for (auto &id : ids)
    {
        Patron *p = patronTable.find(id);
        if (p)
        {
            patrons.append(p);
        }
    }
    return patrons;
}

bool PatronManager::updatePatron(Patron &newPatron)
{
    Patron *oldPatron = patronTable.find(newPatron.getKey());
    if (oldPatron == nullptr)
    {
        return false;
    }

    bool changed = false;

    Array<Field> PatronSchema = patronSchema();

    for(auto &field : PatronSchema){
        changed = newPatron.getField(field.key) != oldPatron->getField(field.key);
    }

    if (!changed)
        return true;

    searchMap.remove(*oldPatron);

    for(auto &field : PatronSchema){
        oldPatron->setField(field.key, newPatron.getField(field.key));
    }

    searchMap.insert(*oldPatron);

    return savePatrons();
}

Array<Patron *> PatronManager::sortPatrons(PatronSortKey key, bool reverse)
{
    Array<Patron *> sortedPatrons = patronTable.all();

    switch (key)
    {
    case PatronSortKey::NAME:
        mergeSort(sortedPatrons, [](Patron *p)
                  { return p->getName(); }, reverse);
        break;
    case PatronSortKey::MEMBERSHIP_DATE:
        mergeSort(sortedPatrons, [](Patron *p)
                  { return p->getMembershipDate(); }, reverse);
        break;
    case PatronSortKey::BORROW_COUNT:
        mergeSort(sortedPatrons, [](Patron *p)
                  { return p->getBorrowCount(); }, reverse);
        break;
    }
    return sortedPatrons;
}

Array<Patron *> PatronManager::getAllPatrons()
{
    return patronTable.all();
}
