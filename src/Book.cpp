#include "Book.hpp"
#include <fstream>
#include <sstream>

using namespace std;

void Book::displayDetails(std::ostream &os) const {
    os << "Title: " << title
       << " | Author: " << author
       << " | ISBN: " << isbn
       << " | Edition: " << edition
       << " | PubYear: " << publicationYear
       << " | Category: " << category
       << " | Available: " << (available ? "Yes" : "No")
       << " | Borrows: " << borrowCount << '\n';
}


void Book::serialize(ostream &ofs) const
{
    ofs << title << "|"
        << author << "|"
        << isbn << "|"
        << edition << "|"
        << publicationYear << "|"
        << category << "|"
        << (available ? "1" : "0") << "|"
        << borrowCount << "\n";
}

void Book::deserialize(const string &line)
{
    std::stringstream ss(line);

    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');
    getline(ss, edition, '|');
    getline(ss, publicationYear, '|');
    getline(ss, category, '|');

    string avail;
    getline(ss, avail, '|');
    available = (avail == "1");

    string bc;
    getline(ss, bc); // borrowCount at end
    borrowCount = stoi(bc);
}
