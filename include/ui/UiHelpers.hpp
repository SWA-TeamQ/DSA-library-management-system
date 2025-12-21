#pragma once
#include <string>
#include <iostream>
using namespace std;

void clearScreen() const;
void printHeader(const string &title) const;
void waitForEnter() const;
string getInput(const string &prompt) const;
void clearInput();
void printDivider() const;

void print(const Book &book) const;
void print(const Patron &patron) const;
void print(const Transaction &transaction) const;