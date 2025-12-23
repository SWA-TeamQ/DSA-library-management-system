#include "utils/utils.hpp"


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
    cin.clear();
    cin.ignore('\n');
}

void waitForEnter(){
    string dummy;
    clearInput();
    getline(cin, dummy);
}

string getString(const string &prompt){
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int getInt(const string &prompt){
    int input;
    bool valid = true;
    do{
        valid = true;
        cout << prompt;
        cin >> input;
        if(cin.fail()){
            cout << "Invalid input. Please enter a valid integer." << endl;
            clearInput();
            valid = false;
        } else {
            clearInput();
            return input;
        }
    } while(valid);
}


