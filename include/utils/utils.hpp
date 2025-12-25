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
string generateId(const string &prefix);
// Date utilities
string addDays(const string &date, int days);
// returns number of days from `from` to `to` (to - from)
int daysBetween(const string &from, const string &to);
string trim( std::string& str);

// escape/unescape fields for pipe-delimited persistence
// Escaping rules:
//  - '\\' -> "\\\\"
//  - '|'  -> "\\|"
//  - '\n' -> "\\n"
string escapeField(const string &s);
string unescapeField(const string &s);
