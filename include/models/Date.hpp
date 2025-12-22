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
    Date(int day, int month, int year) { 
        this->day = day;
        this->month = month;
        this->year = year;
    }

    int getDay() const {
        return day; 
    }
    int getMonth() const { 
        return month; 
    }
    int getYear() const { 
        return year; 
    }

    void setDay(int day) {
        if(day < 1 || day > 31){
            throw invalid_argument("Day cannot be less than 1 or greater than 31");
        }
        this->day = day;
    }
    void setMonth(int month) {
        if(month < 1 || month > 12){
            throw invalid_argument("Month cannot be less than 1 or greater than 12");
        }
        this->month = month;
    }
    void setYear(int year) {
        if(year < 100){
            year = 2000 + year;
        }

        if(year < 2025 || year > 2030){
            throw invalid_argument("Year cannot be less than 2025 or greater than 2030");
        }

        this->year = year;
    }

    void print() const;
    string serialize() const;
    void deserialize(const string &line);
};