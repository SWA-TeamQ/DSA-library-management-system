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
    DataStore(const string &filename = "") : filename(filename) {}

    // any type of map-like object
    template <typename MapType>
    bool saveData(const MapType &dataMap) const
    {
        ofstream file(filename, ios::out | ios::trunc);
        if (!file.is_open()) return false;

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
        if (!file.is_open()) return false;

        file << item.serialize() << '\n';
        file.close();
        return true;
    }

    template <typename MapType>
    bool loadData(MapType &dataMap)
    {
        dataMap.clear();
        ifstream file(filename, ios::in);
        if (!file.is_open()) return false;

        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;
            T item;
            item.deserialize(line);
            dataMap[item.getKey()] = item;
        }
        file.close();
        return true;
    }
};