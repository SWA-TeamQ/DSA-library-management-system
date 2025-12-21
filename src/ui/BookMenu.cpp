#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "models/Book.hpp"
#include "UiHelpers.hpp"

class BookMenu {
public:
    BookMenu() = default;
    void show();

private:
    std::vector<Book> books;

    void listBooks();
    void addBook();
    void removeBook();
    void searchBooks();
    std::string readLine(const std::string& prompt);
    int readInt(const std::string& prompt);
};

std::string BookMenu::readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

int BookMenu::readInt(const std::string& prompt) {
    while (true) {
        std::string s = readLine(prompt);
        try {
            return std::stoi(s);
        } catch (...) {
            std::cout << "Invalid number, try again.\n";
        }
    }
}

void BookMenu::listBooks() {
    if (books.empty()) {
        std::cout << "No books in the library.\n";
        return;
    }
    std::cout << "ID\tTitle\tAuthor\tISBN\n";
    std::cout << "-------------------------------------------\n";
    for (const auto& b : books) {
        print(b);
    }
}

void BookMenu::addBook() {
    std::string title = readLine("Title: ");
    if (title.empty()) { std::cout << "Title cannot be empty.\n"; return; }
    std::string author = readLine("Author: ");
    std::string isbn = readLine("ISBN: ");
    Book b{ nextId++, title, author, isbn };
    books.push_back(std::move(b));
    std::cout << "Book added.\n";
}

void BookMenu::removeBook() {
    int id = readInt("Enter book ID to remove: ");
    auto it = std::find_if(books.begin(), books.end(), [id](const Book& b){ return b.id == id; });
    if (it == books.end()) {
        std::cout << "Book with ID " << id << " not found.\n";
        return;
    }
    books.erase(it);
    std::cout << "Book removed.\n";
}

void BookMenu::searchBooks() {
    std::string q = readLine("Search term (title/author/isbn): ");
    if (q.empty()) { std::cout << "Empty search.\n"; return; }
    std::vector<Book> results;
    for (const auto& b : books) {
        std::string lowerTitle = b.title; std::string lowerAuthor = b.author; std::string lowerIsbn = b.isbn;
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        std::transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);
        std::transform(lowerIsbn.begin(), lowerIsbn.end(), lowerIsbn.begin(), ::tolower);
        std::string ql = q; std::transform(ql.begin(), ql.end(), ql.begin(), ::tolower);
        if (lowerTitle.find(ql) != std::string::npos ||
            lowerAuthor.find(ql) != std::string::npos ||
            lowerIsbn.find(ql) != std::string::npos) {
            results.push_back(b);
        }
    }
    if (results.empty()) {
        std::cout << "No matches found.\n";
        return;
    }
    std::cout << "Matches:\nID\tTitle\tAuthor\tISBN\n";
    for (const auto& b : results) {
        std::cout << b.id << '\t' << b.title << '\t' << b.author << '\t' << b.isbn << '\n';
    }
}

void BookMenu::show() {
    while (true) {
        std::cout << "\n--- Book Menu ---\n"
                  << "1. List books\n"
                  << "2. Add book\n"
                  << "3. Remove book\n"
                  << "4. Search books\n"
                  << "0. Exit menu\n"
                  << "Choice: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume rest of line
        switch (choice) {
            case 1: listBooks(); break;
            case 2: addBook(); break;
            case 3: removeBook(); break;
            case 4: searchBooks(); break;
            case 0: return;
            default: std::cout << "Unknown choice.\n"; break;
        }
    }
}

// If run standalone for quick testing:
#ifdef BOOKMENU_STANDALONE
int main() {
    BookMenu menu;
    menu.show();
    return 0;
}
#endif