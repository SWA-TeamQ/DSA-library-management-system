#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "dsa/Array.hpp"
#include "ui/Schemas.hpp"
#include "ui/UiHelpers.hpp"

using namespace std;

void Row(Array<string> values, bool borderTop = false, int width = 15);

void BookForm(Book &book, Array<Field> schema, bool update = false);

void PatronForm(Patron &patron, Array<Field> schema, bool update = false);
void TransactionForm(Transaction &transaction, Array<Field> schema, bool update = false);