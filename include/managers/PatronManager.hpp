#pragma once
#include <vector>
#include "models/Patron.hpp"
#include "dsa/HashTable.hpp"
#include "core/DataStore.hpp"

class PatronManager
{
private:
    HashTable<Patron> patrons; // Hash table keyed by patronID
    vector<Patron> patronList;
    DataStore<Patron> store;

public:
    PatronManager(const string &filename) : store(filename)
    {
        loadPatrons();
    }

    void loadPatrons();
    void savePatrons();

    bool addPatron(const Patron &p);
    bool removePatron(const string &patronID);
    Patron *findPatron(PatronSearchKey key) const;
    vector<Patron *> findPatrons(PatronSearchKey key) const;
    void sortPatrons(PatronSortKey key, bool reverse = false);
    bool updatePatron(PatronSearchKey key);
    void listAllPatrons() const;
};
