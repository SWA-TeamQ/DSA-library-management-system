#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class DataStore
{
private:
    string filename;

public:
    DataStore(const string &filename)
    {
        this->filename = filename;
    }

    bool saveData(const vector<T> &dataList) const
    {
        ofstream file(filename, ios::out | ios::trunc);

        if (!file.is_open())
        {
            return false;
        }

        // Write each item, one per line
        for (const T &item : dataList)
        {
            file << item.serialize() << '\n';
        }

        file.close();
        return true;
    }

    bool addData(const T &item) const
    {
        ofstream file(filename, ios::app);

        if (!file.is_open())
        {
            return false;
        }

        file << item.serialize() << '\n';
        file.close();
        return true;
    }

    bool loadData(vector<T> &dataList)
    {
        dataList.clear();
        ifstream file(filename, ios::in);

        if (!file.is_open())
        {
            return false;
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
        return true;
    }
};