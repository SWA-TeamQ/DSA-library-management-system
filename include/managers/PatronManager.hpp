#pragma once
#include <string>
#include <iostream>
#include "dsa/Array.hpp"
#include "models/Patron.hpp"
#include "dsa/HashTable.hpp"
#include "core/DataStore.hpp"
#include "PatronSearch.hpp"

using namespace std;

class PatronManager
{
private:
    DataStore<Patron> patronStore;
    HashTable<Patron> patronTable; // ID -> Patron
    PatronSearchMap searchMap;

public:
    PatronManager(string filename) : patronStore(filename)
    {
        loadPatrons();
    }

    void loadPatrons()
    {
        patronTable.clear();
        searchMap.clear();

        if (!patronStore.loadData(patronTable))
        {
            cout << "Warning: Failed to load patrons from file\n";
            return;
        }
        buildSearchMap();
    }

    void savePatrons()
    {
        if (!patronStore.saveData(patronTable))
        {
            cout << "Warning: Failed to save patrons to file\n";
        }
    }

    void buildSearchMap()
    {
        searchMap.buildIndices(patronTable);
    }

    bool addPatron(Patron &p);
    bool removePatron(PatronSearchKey key, string value);
    Patron *findPatron(PatronSearchKey key, string value);
    Array<Patron *> findPatrons(PatronSearchKey key, string value);
    Array<Patron *> sortPatrons(PatronSortKey key, bool reverse = false);
    bool updatePatron(Patron &p);
    Array<Patron *> getAllPatrons();
};
