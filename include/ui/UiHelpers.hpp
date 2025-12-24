#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <climits>
#include <cstdlib> // for system()
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "ui/UiComponents.hpp"
#include "ui/UiHelpers.hpp"
#include "utils/utils.hpp"

using namespace std;

void clearInput();
void waitForEnter();
string readString(const string &prompt, bool optional = false);
int readInt(const string &prompt);
void clearScreen();
void printDivider();
void printHeader(const string &title);
void printWelcomeBanner();

void print(const Book &book);
void print(const Patron &patron);
void print(const Transaction &transaction);

void tablePrint(const Array<Book> &books);
void tablePrint(const Array<Book *> &books);
void tablePrint(const Array<Patron> &patrons);
void tablePrint(const Array<Patron *> &patrons);
void tablePrint(const Array<Transaction> &transactions);
void tablePrint(const Array<Transaction *> &transactions);
