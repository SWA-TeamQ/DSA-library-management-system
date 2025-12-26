#include "ui/UiComponents.hpp"

void Row(Array<string> values, bool borderTop, int width)
{
    size_t totalWidth = values.size() * (width + 3) + 1;
    // border top
    cout << endl;
    if (borderTop)
    {
        for (size_t i = 0; i < totalWidth; i++)
            cout << "-";
    }
    cout << endl;
    for (size_t i = 0; i < values.size(); i++)
    {
        cout << "| " << left << setw(width) << values[i] << " ";
    }
    cout << "|";
    cout << endl;

    // border bottom
    for (size_t i = 0; i < totalWidth; i++)
        cout << "-";
    cout << endl;
}


void BookForm(Book &book, Array<Field> schema, bool update)
{
    for (auto &field : schema)
    {
        string input;
        int number = 0;
        bool isRequired = field.required && !update;

        string prompt = field.label + (field.required ? " *" : "") + ": ";
        cout << field.label << (field.required ? " *" : "") << ": ";

        if (field.type == FieldType::STRING)
        {
            input = readString(prompt, isRequired);
        }
        else if (field.type == FieldType::INTEGER)
        {
            number = readInt(prompt, isRequired);
        }

        if (field.key == "isbn")
        {
            book.setISBN(input);
        }
        else if (field.key == "title")
        {
            book.setTitle(input);
        }
        else if (field.key == "author")
        {
            book.setAuthor(input);
        }
        else if (field.key == "edition")
        {
            book.setEdition(input);
        }
        else if (field.key == "publicationYear")
        {
            book.setPublicationYear(number);
        }
        else if (field.key == "category")
        {
            book.setCategory(input);
        }
        else if (field.key == "totalQuantity")
        {
            book.setTotalQuantity(number);
        }
    }
}

void PatronForm(Patron &patron, Array<Field> schema, bool update)
{
    for (auto &field : schema)
    {
        string input;
        int number = 0;
        bool isRequired = field.required && !update;

        string prompt = field.label + (field.required ? " *" : "") + ": ";
        cout << field.label << (field.required ? " *" : "") << ": ";

        if (field.type == FieldType::STRING)
        {
            input = readString(prompt, isRequired);
        }
        else if (field.type == FieldType::INTEGER)
        {
            number = readInt(prompt, isRequired);
        }

        if (field.key == "patronID")
        {
            patron.setID(input);
        }
        else if (field.key == "name")
        {
            patron.setName(input);
        }
        else if (field.key == "contact")
        {
            patron.setContact(input);
        }
        else if (field.key == "membershipDate")
        {
            patron.setMembershipDate(input);
        }
    }
}

void TransactionForm(Transaction &transaction, Array<Field> schema, bool update)
{
    for (auto &field : schema)
    {
        string input;
        int number = 0;
        bool isRequired = field.required && !update;

        string prompt = field.label + (field.required ? " *" : "") + ": ";
        cout << field.label << (field.required ? " *" : "") << ": ";

        if (field.type == FieldType::STRING)
        {
            input = readString(prompt, isRequired);
        }
        else if (field.type == FieldType::INTEGER)
        {
            number = readInt(prompt, isRequired);
        }
        if (field.key == "transactionID")
        {
            transaction.setId(input);
        }
        else if (field.key == "bookID")
        {
            transaction.setBookID(input);
        }
        else if (field.key == "patronID")
        {
            transaction.setPatronID(input);
        }
        else if (field.key == "borrowDate")
        {
            transaction.setBorrowDate(input);
        }
        else if (field.key == "dueDate")
        {
            transaction.setDueDate(input);
        }
    }
}
