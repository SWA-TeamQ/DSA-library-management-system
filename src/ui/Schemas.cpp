#include "ui/Schemas.hpp"

Array<Field> bookSchema()
{
    Array<Field> schema;
    schema.append(Field{"id", "ISBN", FieldType::STRING, true});
    schema.append(Field{"title", "Title", FieldType::STRING, true});
    schema.append(Field{"author", "Author", FieldType::STRING, true});
    schema.append(Field{"edition", "Edition", FieldType::STRING, true});
    schema.append(Field{"category", "Category", FieldType::STRING, false});
    schema.append(Field{"publicationYear", "Publication Year", FieldType::INTEGER, true});
    schema.append(Field{"totalQuantity", "Total Copies", FieldType::INTEGER, true});

    return schema;
}

Array<Field> patronSchema()
{
    Array<Field> schema;
    schema.append(Field{"id", "ID", FieldType::STRING, true});
    schema.append(Field{"name", "Name", FieldType::STRING, true});
    schema.append(Field{"contact", "Contact", FieldType::STRING, true});
    schema.append(Field{"membershipDate", "Membership Date (YYYY-MM-DD)", FieldType::STRING, true});
    
    return schema;
}

Array<Field> transactionSchema()
{
    Array<Field> schema;
    schema.append(Field{"id", "ID", FieldType::STRING, true});
    schema.append(Field{"bookID", "Book ID", FieldType::STRING, true});
    schema.append(Field{"patronID", "Patron ID", FieldType::STRING, true});
    schema.append(Field{"borrowDate", "Borrow Date (YYYY-MM-DD)", FieldType::STRING, true});
    schema.append(Field{"dueDate", "Due Date (YYYY-MM-DD)", FieldType::STRING, true});
    
    return schema;
}
