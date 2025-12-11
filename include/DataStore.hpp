#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// this class a generic layer for storing data about each components of this lms

template <typename T>
class DataStore
{
private: 
    string filename;

public:
    DataStore(string filename){
        this->filename = filename;
    }

    void saveData(const vector<T> &dataList) {
      ofstream dataFile(filename, ios::binary);
        if (!dataFile) {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
            return;
        }

        size_t count = dataList.size();
        dataFile.write(reinterpret_cast<const char*>(&count), sizeof(count)); // store number of items

        for (const auto &data : dataList) {
            data.serialize(dataFile); // call the object's serialize
        }
    }


    void loadData(vector<T> &dataList) {
         ifstream dataFile(filename, ios::binary);
        if (!dataFile) {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
            return;
        }

        size_t count;
        dataFile.read(reinterpret_cast<char*>(&count), sizeof(count)); // read number of items

        for (size_t i = 0; i < count; ++i) {
            T data;
            data.deserialize(dataFile); // call the object's deserialize
            dataList.push_back(data);
        }
    }
};