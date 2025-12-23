#include "ui/BookMenu.hpp"

void BookMenu::show()
{
    bool running = true;
    while (running)
    {
        printHeader("Book Menu");
        cout << "1. List books\n"
             << "2. Add book\n"
             << "3. Remove book\n"
             << "4, Update book\n"
             << "5. Search books\n"
             << "6. Sort books\n"
             << "0. Back\n";

        int choice = readInt("Choose: ");

        switch (choice)
        {
        case 0:
            running = false;
            break;
        case 1:
            listBooks();
            break;
        case 2:
            addBook();
            break;
        case 3:
            removeBook();
            break;
        case 4:
            updateBook();
            break;
        case 5:
            searchBooks();
            break;
        case 6:
            sortBooks();
            break;
        default:
            cout << "Unknown choice.\n";
            break;
        }
    }
}

void BookMenu::listBooks()
{
    Array<Book *> books = controller.listAllBooks();
    tablePrint(books);
}

void BookMenu::addBook()
{
    printHeader("Add Book");
    Book newBook;
    newBook.setTitle(readString("Title: "));
    newBook.setAuthor(readString("Author: "));
    newBook.setISBN(readString("ISBN: "));
    newBook.setEdition(readString("Edition: "));
    newBook.setPublicationYear(readInt("Publication year: "));
    newBook.setCategory(readString("Category: "));

    if (controller.addBook(newBook))
        cout << "Book added successfully.\n";
    else
        cout << "A book with this ISBN already exists.\n";
    waitForEnter();
}

void BookMenu::removeBook()
{
    printHeader("Remove Book");
    string isbn = readString("Enter ISBN: ");

    if (controller.removeBook(isbn))
        cout << "Book removed.\n";
    else
        cout << "Book not found.\n";
    waitForEnter();
}

void BookMenu::updateBook()
{
    printHeader("Update Book");
    waitForEnter();
}

void BookMenu::searchBooks()
{
    printHeader("Search Books");
    cout << "1. By ISBN\n"
         << "2. By title\n"
         << "3. By author\n"
         << "0. Back\n";
    int choice = readInt("Choose: ");

    switch (choice)
    {
        case 0:
            return;
        case 1:
        {
            string isbn = readString("ISBN: ");
            if (auto *book = controller.findBook(isbn))
                print(*book);
            else
                cout << "Book not found.\n";
            break;
        }
        case 2:
        {
            string title = readString("Title contains: ");
            Array<Book *> books = controller.findBooksByTitle(title);
            tablePrint(books);
            break;
        }
        case 3:
        {
            string author = readString("Author contains: ");
            Array<Book *> books = controller.findBooksByAuthor(author);
            tablePrint(books);
            break;
        }
        default:
            return;
    }
    waitForEnter();
}

void BookMenu::sortBooks()
{
    printHeader("Sort Books");
    cout << "1. Title\n"
         << "2. Author\n"
         << "3. Publication year\n"
         << "4. Borrow count\n"
         << "0. Back\n";
    string field = readString("Sort by: ");
    if (field == "0")
        return;

    string order = readString("Reverse order? (y/n): ");
    bool reverse = (order == "y" || order == "Y");

    Array<Book *> books;

    int choice = readInt("Choose: ");
    switch (choice)
    {
    case 0:
        return;
    case 1:
        books = controller.sortBooksByTitle(reverse);
        break;

    case 2:
        books = controller.sortBooksByAuthor(reverse);
        break;

    case 3:
        books = controller.sortBooksByYear(reverse);
        break;
    case 4:
        books = controller.sortBooksByBorrowCount(reverse);
        break;
    default:
        cout << "Invalid inptu \n";
        return;
    }

    tablePrint(books);
    waitForEnter();
}
