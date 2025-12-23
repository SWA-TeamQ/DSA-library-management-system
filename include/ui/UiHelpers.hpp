#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib> // for system()
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "ui/UiComponents.hpp"
#include "utils/utils.hpp"

using namespace std;

void clearScreen();
void printHeader(const string &title);
int getInt(const string &prompt);
void clearInput();
void printDivider();

void print(const Book &book);
void print(const Patron &patron);
void print(const Transaction &transaction);

void tablePrint(const Array<Book> &books);
void tablePrint(const Array<Patron> &patrons);
void tablePrint(const Array<Transaction> &transactions);