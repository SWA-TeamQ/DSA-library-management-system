#include "models/Transaction.hpp"
#include "utils/utils.hpp"
#include <sstream>

using namespace std;

bool Transaction::isOverdue() 
{
    if (returned)
        return false;

    // Dates are YYYY-MM-DD → string comparison works
    return returnDate.empty() && getCurrentDate() > dueDate;
}

void Transaction::markReturned()
{
    returned = true;
    returnDate = getCurrentDate();
}

double Transaction::calculateFine(double dailyRate) 
{
    // If transaction was returned, compute fine based on return date
    string effectiveDate = returnDate.empty() ? getCurrentDate() : returnDate;
    // If effective date is not after dueDate -> no fine
    if (effectiveDate <= dueDate) return 0.0;
    int days = daysBetween(dueDate, effectiveDate);
    if (days <= 0) return 0.0;
    return days * dailyRate;
}

string Transaction::serialize()
{
    return transactionID + "|" + bookID + "|" + patronID + "|" + borrowDate + "|" + dueDate + "|" + returnDate + "|" + (returned ? "1" : "0");
}

void Transaction::deserialize(const string &line)
{
    stringstream ss(line);
    string field;

    getline(ss, transactionID, '|');
    getline(ss, bookID, '|');
    getline(ss, patronID, '|');
    getline(ss, borrowDate, '|');
    getline(ss, dueDate, '|');
    getline(ss, returnDate, '|');
    getline(ss, field);
    returned = (field == "1");
}

Array<string> Transaction::getFields() 
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

Array<string> Transaction::getValues() 
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
