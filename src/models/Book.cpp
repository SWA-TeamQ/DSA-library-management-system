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
           int TotalQuantity,
           int currentQuantity,
           int borrowCount)
{
  this->title = title;
  this->author = author;
  this->isbn = isbn;
  this->edition = edition;
  this->publicationYear = publicationYear;
  this->category = category;
  this->TotalQuantity = TotalQuantity;
  this->currentQuantity = currentQuantity;
  
  this->borrowCount = borrowCount;
}

string Book::serialize() const
{
  return title + "," + author + "," + isbn + "," + edition + "," +
         to_string(publicationYear) + "," + category + "," + to_string(TotalQuantity) + "," + to_string(currentQuantity) + "," + "," + to_string(borrowCount);
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
    TotalQuantity = stoi(field);
  else
    TotalQuantity = 0;
  getline(ss, field, ',');
  if (!field.empty())
    currentQuantity = stoi(field);
  else
    currentQuantity = 0;
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
  Array<string> fields;
  fields.append("Title");
  fields.append("Author");
  fields.append("ISBN");
  fields.append("Edition");
  fields.append("Publication Year");
  fields.append("Category");
  fields.append("Total Quantity");
  fields.append("Current Quantity");
  fields.append("Borrow Count");
  return fields;
}

Array<string> Book::getValues() const
{
  Array<string> values;
  values.append(title);
  values.append(author);
  values.append(isbn);
  values.append(edition);
  values.append(to_string(publicationYear));
  values.append(category);
  values.append(to_string(TotalQuantity));
  values.append(to_string(currentQuantity));
  values.append(to_string(borrowCount));
  return values;
}