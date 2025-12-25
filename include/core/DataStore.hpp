#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
template <typename T>
class DataStore
{
private:
    string filename;

public:
    DataStore(string filename)
    {
        this->filename = "data/" + filename;
    }

    bool saveData(HashTable<T> &dataMap)
    {
        ofstream file(filename, ios::out | ios::trunc);
        if (!file.is_open())
            return false;

        for (auto &[key, item] : dataMap)
        {
            file << item.serialize() << "\n";
        }
        file.close();
        return true;
    }

    bool addData(T &item)
    {
        ofstream file(filename, ios::app);
        if (!file.is_open())
            return false;

        file << item.serialize() << '\n';
        file.close();
        return true;
    }

    bool loadData(HashTable<T> &dataMap)
    {
        dataMap.clear();
        ifstream file(filename, ios::in);
        if (!file.is_open())
            return false;

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue;
            T item;
            item.deserialize(line);
            dataMap[item.getKey()] = item;
        }
        file.close();
        return true;
    }
};