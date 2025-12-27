#pragma once
#define RESET   "\033[0m"
#define GRAY    "\033[38;5;237m"  // Bright Black / Dark Gray
#define WHITE   "\033[37m"  // Standard White

#include <iostream>
#include <iomanip>
#include <string>
#include "models/Book.hpp"
#include "models/Patron.hpp"
#include "models/Transaction.hpp"
#include "dsa/Array.hpp"
#include "ui/Schemas.hpp"
#include "ui/UiHelpers.hpp"
#include "utils/utils.hpp"



using namespace std;

void Row(Array<string> values, bool borderTop = false, int width = 15);

void print(Book &book);
void print(Patron &patron);
void print(Transaction &transaction);

void tablePrint(Array<Book> &books);
void tablePrint(Array<Book *> &books);
void tablePrint(Array<Patron> &patrons);
void tablePrint(Array<Patron *> &patrons);
void tablePrint(Array<Transaction> &transactions);
void tablePrint(Array<Transaction *> &transactions);

template <typename T>
void Form(T &obj, Array<Field> schema, bool update)
{
    for (auto &field : schema)
    {
        if(update && field.key == "id") {
            // skip id field during update
            continue;
        }

        string input;
        int number;
        string prompt;

        bool isOptional = !field.required || update; // if the field is required and we are not updating, then it is required
  
        // this is the input prompt
        if(update){
            prompt = field.label + " [default=" + obj.getField(field.key) + "]: ";
        }
        else{
            prompt = field.label + (field.required ? " *" : "") + ": ";
        }

        // if the field is type of string
        if (field.type == FieldType::STRING)
        {
            if (update)
            {
                string fallbackValue = obj.getField(field.key);
                input = readString(prompt, isOptional, fallbackValue);
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
                int fallbackValue = stoi(obj.getField(field.key));
                number = readInt(prompt, isOptional, fallbackValue);
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
