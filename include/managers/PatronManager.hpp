#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "models/Patron.hpp"
#include "dsa/HashTable.hpp"
#include "core/DataStore.hpp"
#include "PatronSearch.hpp"

using namespace std;

class PatronManager
{
private:
    DataStore<string, Patron> patronStore;
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
    bool removePatron(const string &patronID);
    Patron *findPatron(const string &patronID) const;

    void displayAll() const;
};

