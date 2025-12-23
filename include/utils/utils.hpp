#pragma once
#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

string getCurrentDate();
string generateId(const string &prefix);
void clearInput();

void waitForEnter();
string getString(const string &prompt);
int getInt(const string &prompt);
