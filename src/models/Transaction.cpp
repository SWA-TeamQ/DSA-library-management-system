#include "models/Transaction.hpp"
#include <sstream>

using namespace std;

bool Transaction::isOverdue() const
{
    // Simplified: assume overdue if not returned
    return !returned;
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

void Transaction::displayDetails() const
{
    cout << "Transaction ID: " << transactionID
         << " | Book ID: " << bookID
         << " | Patron ID: " << patronID
         << " | Borrow Date: " << borrowDate
         << " | Due Date: " << dueDate
         << " | Return Date: " << returnDate
         << " | Returned: " << (returned ? "Yes" : "No") << '\n';
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
