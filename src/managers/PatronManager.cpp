#include "managers/PatronManager.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

bool PatronManager::addPatron(const Patron &p)
{
    int index = patronList.size();
    patronList.push_back(p);
    patronTable.insert(p.getKey(), index);
    searchMap.insert(p);
    patronStore.addData(p);
    return true;
}

bool PatronManager::removePatron(const string &patronID)
{
    int *indexPtr = patronTable.find(patronID);
    if (!indexPtr)
        return false;

    int index = *indexPtr;
    Patron p = patronList[index];
    
    searchMap.remove(p);
    patronList.erase(patronList.begin() + index);
    
    savePatrons();
    buildSearchIndex();

    return true;
}

Patron *PatronManager::findPatron(const string &patronID) const
{
    int *indexPtr = patronTable.find(patronID);
    if(!indexPtr){
        return nullptr;
    }
    return &patronList[*indexPtr]);
}

void PatronManager::sortPatrons(const PatronSortKey &key, bool reverse)
{
    // Placeholder for sorting logic if needed
}

bool PatronManager::updatePatron(const Patron &newPatron)
{
    int *indexPtr = patronTable.find(newPatron.getKey());
    if(!indexPtr){
        return false;
    }

    Patron &oldPatron = patronList[*indexPtr];
    if(newPatron.getName() != oldPatron.getName() || 
       newPatron.getContact() != oldPatron.getContact() || 
       newPatron.getMembershipDate() != oldPatron.getMembershipDate() || 
       newPatron.getBorrowCount() != oldPatron.getBorrowCount()){
           searchMap.remove(oldPatron);
           oldPatron = newPatron;
           searchMap.insert(oldPatron);
       }
    
    savePatrons();
    return true;
}
