#include "Book.hpp"
#include <fstream>
using namespace std;

void Book::displayDetails(ostream& os) const {
    os << "Title: " << title << " | Author: " << author
       << " | ISBN: " << isbn << " | Edition: " << edition
       << " | PubYear: " << publicationYear << " | Cat: " << category
       << " | Avail: " << (available ? "Yes" : "No")
       << " | Borrows: " << borrowCount << '\n';
}

void Book::serialize(ofstream &ofs) const {
    auto writeString = [&](const string &s) {
        size_t len = s.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(s.c_str(), len);
    };

    writeString(title);
    writeString(author);
    writeString(isbn);
    writeString(edition);
    writeString(publicationYear);
    writeString(category);

    ofs.write(reinterpret_cast<const char*>(&available), sizeof(available));
    ofs.write(reinterpret_cast<const char*>(&borrowCount), sizeof(borrowCount));
}

void Book::deserialize(ifstream &ifs) {
    auto readString = [&](string &s) {
        size_t len;
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        s.resize(len);
        ifs.read(&s[0], len);
    };

    readString(title);
    readString(author);
    readString(isbn);
    readString(edition);
    readString(publicationYear);
    readString(category);

    ifs.read(reinterpret_cast<char*>(&available), sizeof(available));
    ifs.read(reinterpret_cast<char*>(&borrowCount), sizeof(borrowCount));
}
