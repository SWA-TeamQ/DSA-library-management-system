#include "DataStore.hpp"
#include <vector>
using namespace std;

template <typename T>
class DataStore
{
private:
    const string filename;

public:
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

};