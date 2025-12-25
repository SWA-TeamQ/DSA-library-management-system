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
    DataStore(const string &filename){
        this->filename = "data/" + filename;
    }

    bool saveData(const HashTable<T> &dataMap) const
    {
        ofstream file(filename, ios::out | ios::trunc);
        if (!file.is_open()) return false;

        for (const auto &[key, item] : dataMap)
        {
            file << item.serialize() << "\n";
        }
        file.close();
        return true;
    }

    bool addData(const T &item)
    {
        ofstream file(filename, ios::app);
        if (!file.is_open()) return false;

        file << item.serialize() << '\n';
        file.close();
        return true;
    }

    bool loadData(HashTable<T> &dataMap)
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