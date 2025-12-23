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
    HashTable<string, Patron> patronTable; // ID -> Patron
    PatronSearchMap searchMap;

public:
    PatronManager(const string &filename) : patronStore(filename)
    {
        loadPatrons();
    }

    void loadPatrons(){
        patronTable.clear();
        searchMap.clear();

        if(!patronStore.loadData(patronTable)){
            cout << "Warning: Failed to load patrons from file\n";
            return;
        }
        buildSearchMap();
    }

    void savePatrons(){
        if(!patronStore.saveData(patronTable)){
            cout << "Warning: Failed to save patrons to file\n";
        }
    }

    void buildSearchMap(){
        searchMap.buildIndices(patronTable);
    }

    bool addPatron(const Patron &p);
    bool removePatron(const PatronSearchKey key, const string &value);
    Patron *findPatron(const PatronSearchKey key, const string &value) const;
    Array<Patron *> findPatrons(const PatronSearchKey key, const string &value) const;
    Array<Patron *> sortPatrons(const PatronSortKey key, bool reverse = false);
    bool updatePatron(const Patron &p);
    Array<Patron *> getAllPatrons() const;
};

