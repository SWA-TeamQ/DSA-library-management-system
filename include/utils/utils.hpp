#pragma once
#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cctype>

using namespace std;

string getCurrentDate();
string generateId(string prefix);
/* Date utilities */
string addDays(string date, int days);
// returns number of days from `from` to `to` (to - from)
int daysBetween(string from, string to);
string trim(string str);
string truncate(string str, size_t width);
string toLower(string s);
