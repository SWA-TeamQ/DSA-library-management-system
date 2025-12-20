#include "../../includes/utils/utils.hpp"
#include <ctime>
#include <cmath>
#include <cctype> // For isdigit, isalpha, isspace
#include <cstdio> // For sscanf

using namespace std;

namespace Utils {

    //  getCurrentDate()
    string getCurrentDate() {
        time_t now = time(nullptr);
        struct tm tstruct = {};
        char buf[80];
        
        // Use secure localtime_s for Windows or localtime for POSIX if needed
        // Assuming standard C++ for portability, or usage in user environment
        #if defined(_MSC_VER)
            localtime_s(&tstruct, &now);
        #else
            tstruct = *localtime(&now);
        #endif

        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
        return string(buf);
    }

    // daysBetween(d1, d2)
    int daysBetween(const string& d1, const string& d2) {
        struct tm tm1 = {};
        struct tm tm2 = {};

        int y1, m1, d1_val, y2, m2, d2_val;
        
        // Simple parsing expecting YYYY-MM-DD
        // Note: sscanf is standard C, no std:: namespace needed typically, but strictly it's in <cstdio>
        if (sscanf(d1.c_str(), "%d-%d-%d", &y1, &m1, &d1_val) != 3) return 0;
        if (sscanf(d2.c_str(), "%d-%d-%d", &y2, &m2, &d2_val) != 3) return 0;

        tm1.tm_year = y1 - 1900;
        tm1.tm_mon = m1 - 1;
        tm1.tm_mday = d1_val;

        tm2.tm_year = y2 - 1900;
        tm2.tm_mon = m2 - 1;
        tm2.tm_mday = d2_val;

        time_t time1 = mktime(&tm1);
        time_t time2 = mktime(&tm2);
        
        if (time1 == -1 || time2 == -1) return 0;

        const double SECONDS_PER_DAY = 60.0 * 60.0 * 24.0;
        double difference = difftime(time2, time1);
        
        return abs(static_cast<int>(round(difference / SECONDS_PER_DAY)));
    }

    //  isValidNumber(input)
    bool isValidNumber(const string& input) {
        if (input.empty()) return false;
        for (unsigned char c : input) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    // isValidISBN(isbn)
    bool isValidISBN(const string& isbn) {
        string cleanIsbn;
        // Remove hyphens
        for (char c : isbn) {
            if (c != '-') cleanIsbn += c;
        }

        size_t len = cleanIsbn.length();
        if (len != 10 && len != 13) return false;

        for (size_t i = 0; i < len; ++i) {
            char c = cleanIsbn[i];
            
            // Allow 'X' only as the last character of an ISBN-10
            if (i == len - 1 && len == 10 && (c == 'X' || c == 'x')) {
                continue;
            }

            if (!isdigit(static_cast<unsigned char>(c))) return false;
        }

        return true;
    }

    //  isValidName(name) 
    bool isValidName(const string& name) {
        if (name.empty()) return false;
        for (unsigned char c : name) {
            if (!isalpha(c) && !isspace(c)) return false;
        }
        return true;
    }
}