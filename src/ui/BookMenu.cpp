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
    waitForEnter();
}

void BookMenu::removeBook()
{
    printHeader("Remove Book");
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
        string isbn = readString("Enter ISBN: ");
        if (controller.removeBookById(isbn))
            cout << "Book removed.\n";
        else
            cout << "Book not found.\n";
        break;
    }
    case 2:
    {
        string title = readString("Enter title: ");
        if (controller.removeBookByTitle(title))
            cout << "Book removed.\n";
        else
            cout << "Book not found.\n";
        break;
    }
    case 3:
    {
        string author = readString("Enter author: ");
        if (controller.removeBookByAuthor(author))
            cout << "Book removed.\n";
        else
            cout << "Book not found.\n";
        break;
    }
    default:
        cout << "Invalid choice.\n";
        break;
    }
    waitForEnter();
}

void BookMenu::addBook()
{
    printHeader("Add Book");
    Book newBook;
    Form<Book>(newBook, bookSchema(), false);

    if (controller.addBook(newBook))
        cout << "Book added successfully.\n";
    else
        cout << "A book with this ISBN already exists.\n";
    waitForEnter();
}

void BookMenu::updateBook()
{
    printHeader("Update Book");
    cout << "Enter the ISBN of the book to update:\n";
    string isbn = readString("Enter ISBN: ");
    auto *book = controller.findBookById(isbn);

    if (!book)
    {
        cout << "Book not found.\n";
        waitForEnter();
        return;
    }

    // show previous book details if the book is found
    cout << "Current details:\n";
    print(*book);

    Form(*book, bookSchema(), true); // show the book update form

    if (controller.updateBook(*book))
    {
        cout << "Book updated.\n";
    }
    else
    {
        cerr << "Error occured during update" << endl;
    }

    waitForEnter();
}

void BookMenu::searchBooks()
{
    printHeader("Search Books");
    cout << "1. By ISBN\n"
         << "2. By title\n"
         << "3. By author\n"
         << "4. By category\n"
         << "0. Back\n";
    int choice = readInt("Choose: ");

    switch (choice)
    {
    case 0:
        return;
    case 1:
    {
        string isbn = readString("ISBN: ");
        if (auto *book = controller.findBookById(isbn))
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
    case 4:
    {
        string category = readString("Category: ");
        Array<Book *> books = controller.findBooksByCategory(category);
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

    int choice = readInt("Sort By: ");
    if (choice == 0)
        return;

    string order = toLower(readString("Reverse order? (y/n): "));
    bool reverse = (order == "y");

    Array<Book *> books;

    switch (choice)
    {
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
