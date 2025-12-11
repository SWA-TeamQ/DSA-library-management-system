#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// this class a generic layer for storing data about each components of this lms

template <type T>
class DataStore
{
    private string filename{"library_data.txt"};

    DataStore(string filename){
        this->filename = filename;
    }

    void saveData(const vector<T> &dataList) {
        ofstream dataFile(filename, ios::binary);
        if (dataFile.is_open()) {
            for (const auto &data : dataList) {
                dataFile.write(reinterpret_cast<const char*>(&data), sizeof(T));
            }
            dataFile.close();
        } else {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
        }
    }


    void loadData(vector<T> &dataList) {
        ifstream dataFile(filename, ios::binary);
        if (dataFile.is_open()) {
            T data;
            while (dataFile.read(reinterpret_cast<char*>(&data), sizeof(T))) {
                dataList.push_back(data);
            }
            dataFile.close();
        } else {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
        }
    }

    

}