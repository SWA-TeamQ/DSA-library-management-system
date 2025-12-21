#include "managers/PatronManager.hpp"
#include <algorithm>

void PatronManager::loadPatrons()
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

Patron *PatronManager::findPatron(const string &patronID) const
{
    return patrons.find(patronID);
}

void PatronManager::displayAll() const
{
    cout << "--- Patrons ---\n";
    for (auto *p : patrons.all())
        p->displayDetails();
}
