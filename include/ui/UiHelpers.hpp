#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib> // for system()
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "ui/UiComponents.hpp"

using namespace std;

void clearInput();
void waitForEnter();
string getString(const string &prompt);
int getInt(const string &prompt);
void clearScreen();
void printDivider();
void printHeader(const string &title);
void printWelcomeBanner();

void print(const Book &book);
void print(const Patron &patron);
void print(const Transaction &transaction);

void tablePrint(const Array<Book> &books);
void tablePrint(const Array<Patron> &patrons);
void tablePrint(const Array<Transaction> &transactions);