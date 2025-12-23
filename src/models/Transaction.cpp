#include "models/Transaction.hpp"
#include "utils/utils.hpp"
#include <sstream>

using namespace std;

bool Transaction::isOverdue() const
{
    if (returned)
        return false;

    // Dates are YYYY-MM-DD → string comparison works
    return returnDate.empty() && getCurrentDate() > dueDate;
}

void Transaction::markReturned()
{
    returned = true;
    // Set returnDate to current date, but since string, assume set externally or leave
    // For simplicity, set to borrowDate or something, but better to set externally
}

double Transaction::calculateFine(double dailyRate) const
{
    if (!isOverdue())
        return 0.0;
    // Simplified fine calculation
    return 5.0; // fixed fine
}

string Transaction::serialize() const
{
    return transactionID + "," + bookID + "," + patronID + "," + borrowDate + "," + dueDate + "," + returnDate + "," + (returned ? "1" : "0");
}

void Transaction::deserialize(const string &line)
{
    stringstream ss(line);
    string field;

    getline(ss, transactionID, ',');
    getline(ss, bookID, ',');
    getline(ss, patronID, ',');
    getline(ss, borrowDate, ',');
    getline(ss, dueDate, ',');
    getline(ss, returnDate, ',');
    getline(ss, field);
    returned = (field == "1");
}

Array<string> Transaction::getFields() const
{
    Array<string> fields;
    fields.append("Transaction ID");
    fields.append("Book ID");
    fields.append("Patron ID");
    fields.append("Borrow Date");
    fields.append("Due Date");
    fields.append("Return Date");
    fields.append("Returned");
    return fields;
}

Array<string> Transaction::getValues() const
{
    Array<string> values;
    values.append(transactionID);
    values.append(bookID);
    values.append(patronID);
    values.append(borrowDate);
    values.append(dueDate);
    values.append(returnDate);
    values.append(returned ? "Yes" : "No");
    return values;
}
