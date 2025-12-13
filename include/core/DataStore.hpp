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
    DataStore(string filename)
    {
        this->filename = filename;
    }

    void saveData(const vector<T> &dataList)
    {
        ofstream file(filename, ios::out|ios::trunc);

        if (!file.is_open())
        {
            cerr << "Error: Unable to open file for overwriting: " << filename << endl;
            return;
        }

        // Write each item, one per line
        for (const T &item : dataList)
        {
            file << item.serialize() << '\n';
        }

        file.close();
    }

    void loadData(vector<T> &dataList)
    {
        dataList.clear();
        ifstream file(filename,ios::in);

        if (!file.is_open())
        {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue; // skip blank lines

            T item;
            item.deserialize(line);
            dataList.push_back(item);
        }
        file.close();
    }
};