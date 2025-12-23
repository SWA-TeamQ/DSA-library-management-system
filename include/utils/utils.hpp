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
// Date utilities
string addDays(const string &date, int days);
// returns number of days from `from` to `to` (to - from)
int daysBetween(const string &from, const string &to);

