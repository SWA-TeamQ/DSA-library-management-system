#include "Book.hpp"
using namespace std;

void Book::displayDetails(ostream& os) const {
    os << "Title: " << title << " | Author: " << author
       << " | ISBN: " << isbn << " | Cat: " << category
       << " | Avail: " << (available ? "Yes" : "No")
       << " | Borrows: " << borrowCount << '\n';
}
