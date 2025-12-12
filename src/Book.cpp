#include "Book.hpp"
#include <fstream>
#include <sstream>

using namespace std;

void Book::displayDetails()
{
    cout << "Title: " << title
       << " | Author: " << author
       << " | ISBN: " << isbn
       << " | Edition: " << edition
       << " | PubYear: " << publicationYear
       << " | Category: " << category
       << " | Available: " << (available ? "Yes" : "No")
       << " | Borrows: " << borrowCount << '\n';
}

string Book::serialize() const
{
    return title + "," + author + "," + isbn + "," + edition + "," +
           publicationYear + "," + category + "," + (available ? "1" : "0") + "," + to_string(borrowCount);
}

void Book::deserialize(const string &line)
{
    std::stringstream ss(line);
    string field;

    getline(ss, title, ',');
    getline(ss, author, ',');
    getline(ss, isbn, ',');
    getline(ss, edition, ',');
    getline(ss, publicationYear, ',');
    getline(ss, category, ',');
    getline(ss, field, ',');
    available = (field == "1");
    getline(ss, field);
    if(!field.empty()){
        borrowCount = stoi(field);
    }
    else{
        borrowCount = 0;
    }
}
