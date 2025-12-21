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
    vector<Patron> patronList;
    HashTable<string, int> patronTable; // ID -> index
    PatronSearchMap searchMap;
    DataStore<Patron> patronStore;

public:
    PatronManager(const string &filename) : patronStore(filename)
    {
        loadPatrons();
    }

    void loadPatrons(){
        patronList.clear();
        patronTable.clear();
        searchMap.clear();

        if(!patronStore.loadData(patronList)){
            cout << "Warning: Failed to load patrons from file\n";
            return;
        }
        buildSearchIndex();
        buildSearchMap();
    }

    void savePatrons(){
        if(!patronStore.saveData(patronList)){
            cout << "Warning: Failed to save patrons to file\n";
        }
    }

    void buildSearchIndex(){
        patronTable.clear();
        for(int i = 0; i < (int)patronList.size(); i++)
            patronTable.insert(patronList[i].getKey(), i);
    }

    void buildSearchMap(){
        searchMap.buildIndices(patronList);
    }

    bool addPatron(const Patron &p);
    bool removePatron(const string &patronID);
    Patron *findPatron(const string &patronID) const;
    void sortPatrons(const PatronSortKey &key, bool reverse = false);
    bool updatePatron(const Patron &p);
};
