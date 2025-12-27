#pragma once
#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
#include "dsa/Array.hpp"

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


inline auto findIds = [](unordered_map<string, unordered_set<string>> &index, string &key, Array<string> &result)
{
    key = toLower(key); // this is the map key
    auto it = index.find(key);

    if (it != index.end())
    {
        for (auto &id : it->second)
        {
            result.append(id);
        }
    }
};

inline auto removeIndex = [](unordered_map<string, unordered_set<string>> &index, string &id, string &key)
{
    key = toLower(key); // this is the map key
    auto it = index.find(key);
    if (it != index.end())
    {
        it->second.erase(id);
        if (it->second.empty())
        {
            index.erase(it);
        }
    }
};