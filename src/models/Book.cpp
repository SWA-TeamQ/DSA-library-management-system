#include "models/Book.hpp"
#include <fstream>
#include <sstream>

using namespace std;

string Book::serialize() 
{
  return isbn + "|" + title + "|" + author + "|" + edition + "|" +
         to_string(publicationYear) + "|" + category + "|" + to_string(totalQuantity) + "|" + to_string(currentQuantity) + "|" + to_string(borrowCount);
}

void Book::deserialize(string line)
{
  std::stringstream ss(line);
  string field;

  getline(ss, isbn, '|');
  getline(ss, title, '|');
  getline(ss, author, '|');
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

string Book::getField(const string &key)
{
  if (key == "isbn") return isbn;
  if (key == "title") return title;
  if (key == "author") return author;
  if (key == "edition") return edition;
  if (key == "publicationYear") return to_string(publicationYear);
  if (key == "category") return category;
  if (key == "totalQuantity") return to_string(totalQuantity);
  if (key == "currentQuantity") return to_string(currentQuantity);
  if (key == "borrowCount") return to_string(borrowCount);
  return string();
}

bool Book::setField(const string &key, const string &value)
{
  try
  {
    if (key == "isbn") { isbn = value; return true; }
    if (key == "title") { title = value; return true; }
    if (key == "author") { author = value; return true; }
    if (key == "edition") { edition = value; return true; }
    if (key == "publicationYear") { publicationYear = stoi(value); return true; }
    if (key == "category") { category = value; return true; }
    if (key == "totalQuantity") { totalQuantity = stoi(value); currentQuantity = totalQuantity; return true; }
    if (key == "currentQuantity") { currentQuantity = stoi(value); if (currentQuantity > totalQuantity) currentQuantity = totalQuantity; return true; }
    if (key == "borrowCount") { borrowCount = stoi(value); return true; }
  }
  catch (...) { return false; }
  return false;
}

Array<string> Book::getFields()
{
  Array<string> fields;
  fields.append("ISBN");
  fields.append("Title");
  fields.append("Author");
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
  values.append(isbn);
  values.append(title);
  values.append(author);
  values.append(edition);
  values.append(to_string(publicationYear));
  values.append(category);
  values.append(to_string(totalQuantity));
  values.append(to_string(currentQuantity));
  values.append(to_string(borrowCount));
  return values;
}
