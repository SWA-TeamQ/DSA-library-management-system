#include "models/Book.hpp"
#include <fstream>
#include <sstream>

using namespace std;

Book::Book(string title,
           string author,
           string isbn,
           string edition,
           int publicationYear,
           string category,
           int quantity,
           bool available,
           int borrowCount)
{
  this->title = title;
  this->author = author;
  this->isbn = isbn;
  this->edition = edition;
  this->publicationYear = publicationYear;
  this->category = category;
  this->quantity = quantity;
  this->available = available;
  this->borrowCount = borrowCount;
}

void Book::displayDetails() const
{
  cout << "Title: " << title
       << " | Author: " << author
       << " | ISBN: " << isbn
       << " | Edition: " << edition
       << " | PubYear: " << publicationYear
       << " | Category: " << category
       << " | Quantity: " << quantity
       << " | Available: " << (available ? "Yes" : "No")
       << " | Borrows: " << borrowCount << '\n';
}

string Book::serialize() const
{
  return title + "," + author + "," + isbn + "," + edition + "," +
         to_string(publicationYear) + "," + category + "," + to_string(quantity) + "," + (available ? "1" : "0") + "," + to_string(borrowCount);
}

void Book::deserialize(const string &line)
{
  std::stringstream ss(line);
  string field;

  getline(ss, title, ',');
  getline(ss, author, ',');
  getline(ss, isbn, ',');
  getline(ss, edition, ',');
  getline(ss, field, ',');
  if (!field.empty())
    publicationYear = stoi(field);
  else
    publicationYear = -1;
  getline(ss, category, ',');
  getline(ss, field, ',');
  if (!field.empty())
    quantity = stoi(field);
  else
    quantity = 1;
  getline(ss, field, ',');
  available = (field == "1");
  getline(ss, field);
  if (!field.empty())
  {
    borrowCount = stoi(field);
  }
  else
  {
    borrowCount = 0;
  }
}
