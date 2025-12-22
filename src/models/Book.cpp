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
  this->available = available;
  this->borrowCount = borrowCount;
}

string Book::serialize() const
{
  return title + "," + author + "," + isbn + "," + edition + "," +
         to_string(publicationYear) + "," + category + "," + (available ? "1" : "0") + "," + to_string(borrowCount);
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

Array<string> Book::getFields() const
{
  return {
    "Title", 
    "Author", 
    "ISBN", 
    "Edition", 
    "Publication Year", 
    "Category", 
    "Available", 
    "Borrow Count"};
}

Array<string> Book::getValues() const
{
  return {
    title, 
    author, 
    isbn, 
    edition, 
    to_string(publicationYear), 
    category, 
    available ? "available" : "not available", 
    to_string(borrowCount)};
}