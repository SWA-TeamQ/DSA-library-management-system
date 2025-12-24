#include "include/utils/utils.hpp"

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

// parse YYYY-MM-DD into tm (local)
static tm parseDate(const string &date)
{
    tm t{};
    sscanf(date.c_str(), "%d-%d-%d", &t.tm_year, &t.tm_mon, &t.tm_mday);
    t.tm_year -= 1900;
    t.tm_mon -= 1;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    return t;
}

string addDays(const string &date, int days)
{
    tm t = parseDate(date);
    time_t tt = mktime(&t);
    tt += static_cast<time_t>(days) * 24 * 60 * 60;
    tm *res = localtime(&tt);
    stringstream ss;
    ss << put_time(res, "%Y-%m-%d");
    return ss.str();
}

int daysBetween(const string &from, const string &to)
{
    tm tf = parseDate(from);
    tm tt = parseDate(to);
    time_t tfrom = mktime(&tf);
    time_t tto = mktime(&tt);
    double diff = difftime(tto, tfrom);
    return static_cast<int>(diff / (24 * 60 * 60));
}


string trim(string& s)
{
    std::size_t start = 0;
    while (start < s.size() && isspace(s[start]))
        ++start;

    std::size_t end = s.size();
    while (end > start && isspace(s[end - 1]))
        --end;

    return s.substr(start, end - start);
}


