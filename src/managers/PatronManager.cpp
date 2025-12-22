#include "managers/PatronManager.hpp"
#include <iostream>
#include "dsa/MergeSort.hpp"

using namespace std;

bool PatronManager::addPatron(const Patron &p)
{
    patronTable[p.getKey()] = p;
    searchMap.insert(p);
    patronStore.addData(p);
    return true;
}

bool PatronManager::removePatron(const PatronSearchKey key, const string &value)
{
    vector<string> ids;
    switch(key){
        case PatronSearchKey::ID:
            ids.push_back(value);
            break;
        case PatronSearchKey::NAME:
            ids = searchMap.findByName(value);
            break;
    }

    if(ids.empty()){
        return false;
    }

    bool deleted = false;
    for(const auto &id : ids){
        Patron *p = patronTable.find(id);
        if(!p) continue;
        
        // Prevent deletion if patron still has an active borrow
        if(p->isBorrowed()){
            cout << "Patron " << p->getKey() << " has active borrows and cannot be removed" << endl;
            continue;
        }

        deleted = true;
        searchMap.remove(*p);
        patronTable.remove(id);
    }

    if (deleted) {
        savePatrons();
    }
    return deleted;
}

Patron *PatronManager::findPatron(const PatronSearchKey key, const string &value) const
{
    vector<string> ids;
    switch(key){
        case PatronSearchKey::ID:
            ids.push_back(value);
            break;
        case PatronSearchKey::NAME:
            ids = searchMap.findByName(value);
            break;
    }

    if(ids.empty()){
        return nullptr;
    }

    return patronTable.find(ids[0]);
}

vector<Patron *> PatronManager::findPatrons(const PatronSearchKey key, const string &value) const
{
    vector<string> ids;
    switch(key){
        case PatronSearchKey::ID:
            ids.push_back(value);
            break;
        case PatronSearchKey::NAME:
            ids = searchMap.findByName(value);
            break;
    }

    vector<Patron *> patrons;
    for(const auto &id : ids){
        Patron *p = patronTable.find(id);
        if (p) {
            patrons.push_back(p);
        }
    }
    return patrons;
}

bool PatronManager::updatePatron(const Patron &newPatron)
{
    Patron *oldPatron = patronTable.find(newPatron.getKey());
    if(oldPatron == nullptr){
        return false;
    }

    bool changed = false;

    if (newPatron.getName() != oldPatron->getName() || 
        newPatron.getContact() != oldPatron->getContact() ||
        newPatron.getMembershipDate() != oldPatron->getMembershipDate())
    {
        searchMap.remove(*oldPatron);
        oldPatron->setName(newPatron.getName());
        oldPatron->setContact(newPatron.getContact());
        oldPatron->setMembershipDate(newPatron.getMembershipDate());
        searchMap.insert(*oldPatron);
        changed = true;
    }

    if (changed)
    {
        savePatrons();
    }

    return changed;
}

vector<Patron *> PatronManager::sortPatrons(const PatronSortKey key, bool reverse)
{
    vector<Patron *> sortedPatrons = patronTable.all();

    switch(key){
        case PatronSortKey::NAME:
            mergeSort(sortedPatrons, [](const Patron *p){
                return p->getName();
            }, reverse);
            break;
        case PatronSortKey::MEMBERSHIP_DATE:
            mergeSort(sortedPatrons, [](const Patron *p){
                return p->getMembershipDate();
            }, reverse);
            break;
        case PatronSortKey::BORROW_COUNT:
            mergeSort(sortedPatrons, [](const Patron *p){
                return p->getBorrowCount();
            }, reverse);
            break;
    }
    return sortedPatrons;
}

vector<Patron *> PatronManager::getAllPatrons() const
{
    return patronTable.all();
}
