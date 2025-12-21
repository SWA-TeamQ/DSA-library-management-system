#pragma once
#include <vector>
#include <string>
#include "models/Patron.hpp"
#include "dsa/HashTable.hpp"
#include "core/DataStore.hpp"

using namespace std;

class PatronManager
{
private:
    vector<Patron> patronList;
    HashTable<string, int> patronTable; // ID -> index
    DataStore<Patron> store;

public:
    PatronManager(const string &filename) : store(filename)
    {
        loadPatrons();
    }

    void loadPatrons();
    void savePatrons();
    void buildSearchIndex();

    bool addPatron(const Patron &p);
    bool removePatron(const string &patronID);
    Patron *findPatron(const string &patronID) const;
    void sortPatrons(PatronSortKey key, bool reverse = false);
    bool updatePatron(Patron &p);
    void listAllPatrons() const;
};
