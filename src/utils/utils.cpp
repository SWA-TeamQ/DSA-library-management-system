#include "utils/utils.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

string getCurrentDate() {
    time_t t = time(nullptr);
    tm* tm = localtime(&t);
    stringstream ss;
    ss << put_time(tm, "%Y-%m-%d");
    return ss.str();
}

string generateId(const string& prefix) {
    // simple id generator using random (srand) 
    srand(time(nullptr));
    int randomNum = rand() % 100000; // random number between 0 and 99999
    stringstream ss;
    ss << prefix << setw(5) << setfill('0') << randomNum;
    return ss.str();
}

void clearInput(){
    cin.ignore();
    cin.clear();
}

