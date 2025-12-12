#include "Book.hpp"
using namespace std;

Book::Book(const std::string &title,
           const std::string &author,
           const std::string &isbn,
           const std::string &category,
           bool available,
           int borrowCount)
    : title(title), author(author), isbn(isbn),
      category(category), available(available), borrowCount(borrowCount)
{
}

string Book::toCSV() const
{
    return title + "," + author + "," + isbn + "," + category + "," +
           (available ? "1" : "0") + "," +
           to_string(borrowCount);
}

void Book::displayDetails()
{
    cout << "Title: " << title << " | Author: " << author
         << " | ISBN: " << isbn << " | Cat: " << category
         << " | Avail: " << (available ? "Yes" : "No")
         << " | Borrows: " << borrowCount << '\n';
}
