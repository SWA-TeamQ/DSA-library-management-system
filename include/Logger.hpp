#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Logger{
private:
    static const string filename;

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

const string Logger::filename = "library_log.txt";