#include "models/Book.hpp"
#include <fstream>
#include <sstream>

using namespace std;

string Book::serialize() const 
{
  return title + "|" + author + "|" + isbn + "|" + edition + "|" +
         to_string(publicationYear) + "|" + category + "|" + to_string(totalQuantity) + "|" + to_string(currentQuantity) + "|" + to_string(borrowCount);
}

void Book::deserialize(const string &line)
{
  std::stringstream ss(line);
  string field;

  getline(ss, title, '|');
  getline(ss, author, '|');
  getline(ss, isbn, '|');
  getline(ss, edition, '|');
  getline(ss, field, '|');
  publicationYear = stoi(field);
  getline(ss, category, '|');
  getline(ss, field, '|');
  totalQuantity = stoi(field);
  getline(ss, field, '|');
  currentQuantity = stoi(field);
  getline(ss, field);
  borrowCount = stoi(field);
}

Array<string> Book::getFields() 
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

Array<string> Book::getValues() 
{
  Array<string> values;
  values.append(title);
  values.append(author);
  values.append(isbn);
  values.append(edition);
  values.append(to_string(publicationYear));
  values.append(category);
  values.append(to_string(totalQuantity));
  values.append(to_string(currentQuantity));
  values.append(to_string(borrowCount));
  return values;
}
