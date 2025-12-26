#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>
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
string readString(string prompt, bool optional = false);
int readInt(string prompt, bool optional = false);
void clearScreen();
void printDivider();
void printHeader(string title);
void printWelcomeBanner();

void print(Book &book);
void print(Patron &patron);
void print(Transaction &transaction);

void tablePrint(Array<Book> &books);
void tablePrint(Array<Book *> &books);
void tablePrint(Array<Patron> &patrons);
void tablePrint(Array<Patron *> &patrons);
void tablePrint(Array<Transaction> &transactions);
void tablePrint(Array<Transaction *> &transactions);
