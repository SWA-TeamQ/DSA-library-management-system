#include <iostream>
#include <string>

using namespace std;


void Date::print() const {
    cout << serialize() << endl;
}

string Date::serialize() const {
    return to_string(year) + "-" + to_string(month) + "-" + to_string(day);
}

void Date::deserialize(const string &line){
    int values[2];
    
    string temp = "";
    int i = 0;
    for(char &c : line){
        if(c == '-'){
            values[i++] = stoi(temp);
            temp = "";
        }
        else{
            temp += c;
        }
    }
    this->year = values[0];
    this->month = values[1];
    this->day = stoi(temp);
}