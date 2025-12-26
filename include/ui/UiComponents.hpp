#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "dsa/Array.hpp"
#include "ui/Schemas.hpp"
#include "ui/UiHelpers.hpp"

using namespace std;

void Row(Array<string> values, bool borderTop = false, int width = 15);

template <typename T>
void Form(T &obj, Array<Field> schema, bool update)
{
    for (auto &field : schema)
    {
        string input;
        int number;

        bool isRequired = field.required && !update; // if the field is required and we are not updating, then it is required

        // this is the input prompt
        string prompt = field.label + (field.required ? " *" : "") + ": ";

        // if the field is type of string
        if (field.type == FieldType::STRING)
        {
            if (update)
            {
                string fieldKey = obj.getField(field.key);
                input = readString(prompt, isRequired, fieldKey);
            }
            else
            {
                input = readString(prompt);
            }
        }
        // if the field is type of integer
        else if (field.type == FieldType::INTEGER)
        {
            if (update)
            {
                int fieldKey = stoi(obj.getField(field.key));
                number = readInt(prompt, isRequired, fieldKey);
            }
            else
            {
                number = readInt(prompt);
            }
            // change the number into a string so that it will be compatible with the generic setter function
            input = to_string(number);
        }

        // sets the field of the object dynamically
        obj.setField(field.key, input);
    }
}
