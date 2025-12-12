#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// this class is a generic layer for storing data about each component of this lms (books, patrons, transactions) (virtual)

template <typename T>
class DataStore
{
private:
    string filename;

public:
    DataStore(const string &filename)
        : filename(filename) {}

    void saveData(const vector<T> &dataList)
    {
        fstream dataFile(filename, ios::out | ios::trunc);

        if (!dataFile.is_open())
        {
            cerr << "Error: Unable to open file for appending: " << filename << endl;
            return;
        }

        // Write each item, one per line
        for (const auto &item : dataList)
        {
            item.serialize(dataFile); // write to stream (file) (virtual)
            
        }

        dataFile.close();
    }
    

    void loadData(vector<T> &dataList)
    {
       fstream dataFile(filename, ios::in);

        if (!dataFile.is_open())
        {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
            return;
        }
          
        string line;
        while (getline(dataFile, line))
        {
            if (line.empty()) continue; // skip blank lines

            // create a temporary object
            T item;
            item.deserialize(line);  // parse using a deserialize(line) overload (virtual)
            dataList.push_back(item);
        }
        dataFile.close();
    }
};