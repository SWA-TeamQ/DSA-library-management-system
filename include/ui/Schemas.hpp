#pragma once
#include <iostream>
#include <string>
#include "dsa/Array.hpp"

using namespace std;

enum class FieldType
{
    STRING,
    INTEGER
};

struct Field
{
    string key;
    string label;
    FieldType type;
    bool required{true};
};

Array<Field> bookSchema();

Array<Field> patronSchema();

Array<Field> transactionSchema();