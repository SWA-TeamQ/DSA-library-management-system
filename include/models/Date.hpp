#pragma once
#include <string>
#include <iostream>
using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date() = default;
    Date(int d, int m, int y)
    {
        this->day = d;
        this->month = m;
        this->year = y;
    }

    int getDay()
    {
        return day;
    }
    int getMonth()
    {
        return month;
    }
    int getYear()
    {
        return year;
    }

    void setDay(int d)
    {
        if (d < 1 || d > 31)
        {
            throw invalid_argument("Day cannot be less than 1 or greater than 31");
        }
        this->day = d;
    }
    void setMonth(int m)
    {
        if (m < 1 || m > 12)
        {
            throw invalid_argument("Month cannot be less than 1 or greater than 12");
        }
        this->month = m;
    }
    void setYear(int y)
    {
        if (y < 100)
        {
            y = 2000 + y;
        }

        if (y < 2025 || y > 2030)
        {
            throw invalid_argument("Year cannot be less than 2025 or greater than 2030");
        }

        this->year = y;
    }

    string serialize();
    void deserialize(string line);
};