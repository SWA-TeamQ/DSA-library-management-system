#include "Transaction.hpp"
using namespace std;

bool Transaction::isOverdue() const {
    return !returned && chrono::system_clock::now() > dueDate;
}

void Transaction::markReturned() {
    returned = true;
    returnDate = chrono::system_clock::now();
}

double Transaction::calculateFine(double dailyRate) const {
    if (!isOverdue()) return 0.0;
    auto overdueHours = chrono::duration_cast<chrono::hours>(chrono::system_clock::now() - dueDate).count();
    long days = max<long>(1, overdueHours / 24);
    return days * dailyRate;
}

void Transaction::display(ostream& os) const {
    os << "TX:" << transactionID << " Book:" << bookID << " Patron:" << patronID
       << " Returned:" << (returned ? "Yes" : "No")
       << " Overdue:" << (isOverdue() ? "Yes" : "No")
       << " Fine:" << calculateFine() << '\n';
}
