#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static class Logger{
private:
    static const string filename{"library_log.txt"};

public:
    static void logInfo(const string &message) {
        ofstream logFile(filename, ios_base::app);
        if (logFile.is_open()) {
            logFile << "\n[INFO]: " << message << endl;
            logFile.close();
        }
    }

    static void logError(const string &message) {
        ofstream logFile(filename, ios_base::app);
        if (logFile.is_open()) {
            logFile << "\n[ERROR]: " << message << endl;
            logFile.close();
        }
    }
};