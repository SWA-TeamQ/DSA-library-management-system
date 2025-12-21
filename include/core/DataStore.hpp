#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

template <typename U, typename T>
class DataStore
{
private:
    string filename;

public:
    DataStore(const string &filename)
    {
        this->filename = filename;
    }

    bool saveData(const unordered_map<U, T> &dataMap) const
    {
        ofstream file(filename, ios::out | ios::trunc);
        if (!file.is_open()) return false;


        // Write each item, one per line
        for (const auto &[key, item] : dataMap)
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

    bool loadData(unordered_map<U, T> &dataMap)
    {
        dataMap.clear();
        ifstream file(filename, ios::in);

        if (!file.is_open()) return false;

        string line;
        while (getline(file, line))
        {
            // skip blank lines
            if (line.empty()) continue;

            T item;
            item.deserialize(line);
            dataMap[item.getKey()] = item;
        }
        file.close();
        return true;
    }
};