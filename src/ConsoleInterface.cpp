#include "ConsoleInterface.hpp"
#include <iostream>
using namespace std;

void ConsoleInterface::printMainMenu() const {
    cout << "\n=== Library Management System (Educational DSA Edition) ===\n"
         << "1. Add Book\n2. List Books\n3. Add Patron\n4. List Patrons\n5. Borrow Book\n6. Return Book\n0. Exit\nSelect option: ";
}

void ConsoleInterface::handleAddBook() {
    string title, author, isbn, category;
    cout << "Title: "; getline(cin, title);
    cout << "Author: "; getline(cin, author);
    cout << "ISBN: "; getline(cin, isbn);
    cout << "Category: "; getline(cin, category);
    if (title.empty() || author.empty() || isbn.empty()) {
        cout << "Error: Title, Author and ISBN are required.\n";
        return;
    }
    bool ok = controller.addBook(Book(title, author, isbn, category));
    cout << (ok ? "Book added." : "Book not added (duplicate ISBN).") << '\n';
}

void ConsoleInterface::handleListBooks() { controller.listAllBooks(); }

void ConsoleInterface::handleAddPatron() {
    string id, name, contact;
    cout << "Patron ID: "; getline(cin, id);
    cout << "Name: "; getline(cin, name);
    cout << "Contact: "; getline(cin, contact);
    if (id.empty() || name.empty()) { cout << "Error: Patron ID and Name required.\n"; return; }
    bool ok = controller.addPatron(Patron(id, name, contact));
    cout << (ok ? "Patron added." : "Patron not added (duplicate ID).") << '\n';
}

void ConsoleInterface::handleListPatrons() { controller.listAllPatrons(); }

void ConsoleInterface::handleBorrow() {
    string pid, isbn;
    cout << "Patron ID: "; getline(cin, pid);
    cout << "Book ISBN: "; getline(cin, isbn);
    cout << (controller.borrowBook(pid, isbn) ? "Borrow successful." : "Borrow failed.") << '\n';
}

void ConsoleInterface::handleReturn() {
    string pid, isbn;
    cout << "Patron ID: "; getline(cin, pid);
    cout << "Book ISBN: "; getline(cin, isbn);
    cout << (controller.returnBook(pid, isbn) ? "Return processed." : "Return failed.") << '\n';
}

void ConsoleInterface::run() {
    while (running) {
        printMainMenu();
        string choice; getline(cin, choice);
        if      (choice == "1") handleAddBook();
        else if (choice == "2") handleListBooks();
        else if (choice == "3") handleAddPatron();
        else if (choice == "4") handleListPatrons();
        else if (choice == "5") handleBorrow();
        else if (choice == "6") handleReturn();
        else if (choice == "0") { running = false; cout << "Exiting...\n"; }
        else cout << "Invalid option.\n";
    }
}
