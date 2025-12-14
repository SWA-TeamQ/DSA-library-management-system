#pragma once
#include <vector>
#include "models/Patron.hpp"
#include "core/DataStore.hpp"

class PatronManager
{
private:
    vector<Patron> patrons;
    DataStore<Patron> store;

public:
    PatronManager(const string &filename) : store(filename)
    {
        loadPatrons();
    }

    void loadPatrons();
    void savePatrons() const;

    void add(const Patron &p);
    void remove(const string &patronID);

    void displayAll() const;
};
