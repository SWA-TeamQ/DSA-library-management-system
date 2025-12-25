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

        //Need fix: if you are using a key and value ,
        //then u are already setting what type of data container
        // it is, for this case a map
        for (const auto &[key, item] : dataMap)
        {
            file << item.serialize() << "\n";
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
            //NOTE: if a template for the MapType is needed then consider 
            //the use of [] operator as it isn't available in sets
            dataMap[item.getKey()] = item;
        }
        file.close();
        return true;
    }
};