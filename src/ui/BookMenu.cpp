#include "ui/BookMenu.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

BookMenu::BookMenu(LibraryController &controller) : controller(controller) {}

string BookMenu::readLine(const string &prompt) const
{
    cout << prompt;
    string s;
    if (!getline(cin, s))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return {};
    }
    return s;
}

int BookMenu::readInt(const string &prompt) const
{
    while (true)
    {
        string s = readLine(prompt);
        try
        {
            return std::stoi(s);
        }
        catch (...)
        {
            cout << "Invalid number, try again.\n";
        }
    }
}

void BookMenu::waitForEnter() const
{
    cout << "\nPress Enter to continue...";
    string dummy;
    getline(std::cin, dummy);
}

void BookMenu::printBooksTable(const Array<Book *> &books) const
{
    if (books.empty())
    {
        cout << "No books found.\n";
        return;
    }

    cout << std::left
         << std::setw(18) << "ISBN"
         << std::setw(28) << "Title"
         << std::setw(22) << "Author"
         << std::setw(10) << "Year"
         << std::setw(12) << "Available"
         << std::setw(12) << "Borrowed" << '\n';
    cout << string(100, '-') << '\n';

    for (const auto *b : books)
    {
        cout << std::setw(18) << b->getISBN().substr(0, 17)
             << std::setw(28) << b->getTitle().substr(0, 27)
             << std::setw(22) << b->getAuthor().substr(0, 21)
             << std::setw(10) << b->getPublicationYear()
             << std::setw(12) << (b->isAvailable() ? "Yes" : "No")
             << std::setw(12) << b->getBorrowCount() << '\n';
    }
}

void BookMenu::listBooks()
{
    printBooksTable(controller.sortBooks(BookSortKey::TITLE));
    waitForEnter();
}

void BookMenu::addBook()
{
    cout << "\n=== Add Book ===\n";
    string title = readLine("Title: ");
    string author = readLine("Author: ");
    string isbn = readLine("ISBN: ");
    string edition = readLine("Edition: ");
    int year = readInt("Publication year: ");
    string category = readLine("Category: ");

    if (title.empty() || author.empty() || isbn.empty())
    {
        cout << "Title, author, and ISBN are required.\n";
        return;
    }

    Book book(title, author, isbn, edition, year, category);
    if (controller.addBook(book))
    {
        cout << "Book added successfully.\n";
    }
    else
    {
        cout << "A book with this ISBN already exists.\n";
    }
    waitForEnter();
}

void BookMenu::removeBook()
{
    cout << "\n=== Remove Book ===\n";
    string isbn = readLine("Enter ISBN: ");
    if (isbn.empty())
    {
        cout << "ISBN is required.\n";
        return;
    }

    if (controller.removeBook(isbn))
    {
        cout << "Book removed.\n";
    }
    else
    {
        cout << "Book not found.\n";
    }
    waitForEnter();
}

void BookMenu::searchBooks()
{
    cout << "\n=== Search Books ===\n"
         << "1. By title\n"
         << "2. By author\n"
         << "3. By ISBN\n"
         << "0. Back\n";
    int choice = readInt("Choose: ");

    switch (choice)
    {
    case 0:
        return;
    case 1:
    {
        string title = readLine("Title contains: ");
        printBooksTable(controller.findBooksByTitle(title));
        break;
    }
    case 2:
    {
        string author = readLine("Author contains: ");
        printBooksTable(controller.findBooksByAuthor(author));
        break;
    }
    case 3:
    {
        string isbn = readLine("ISBN: ");
        if (auto *book = controller.findBook(isbn))
        {
            printBooksTable(Array<Book *>{book});
        }
        else
        {
            cout << "Book not found.\n";
        }
        break;
    }
    }
    waitForEnter();
}

void BookMenu::sortBooks()
{
    cout << "\n=== Sort Books ===\n"
         << "1. Title\n"
         << "2. Author\n"
         << "3. Publication year\n"
         << "4. Borrow count\n"
         << "0. Back\n";
    string field = readLine("Sort by: ");
    if (field == "0")
        return;

    string order = readLine("Reverse order? (y/n): ");
    bool reverse = (order == "y" || order == "Y");

    BookSortKey key = BookSortKey::TITLE;
    if (field == "2")
        key = BookSortKey::AUTHOR;
    else if (field == "3")
        key = BookSortKey::YEAR;
    else if (field == "4")
        key = BookSortKey::BORROW_COUNT;

    printBooksTable(controller.sortBooks(key, reverse));
    waitForEnter();
}

void BookMenu::show()
{
    bool running = true;
    while (running)
    {
        cout << "\n--- Book Menu ---\n"
             << "1. List books\n"
             << "2. Add book\n"
             << "3. Search books\n"
             << "4. Sort books\n"
             << "5. Remove book\n"
             << "0. Back\n";

        int choice;
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            listBooks();
            break;
        case 2:
            addBook();
            break;
        case 3:
            searchBooks();
            break;
        case 4:
            sortBooks();
            break;
        case 5:
            removeBook();
            break;
        case 0:
            running = false;
            break;
        default:
            cout << "Unknown choice.\n";
            break;
        }
    }
}