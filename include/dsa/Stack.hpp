#pragma once
#include <iostream>
#include "dsa/Array.hpp"

using namespace std;

template <class T>
class Stack
{
private:
    Array<T> objects;

public:
    Stack() = default;

    void push(T obj)
    {
        objects.push_back(obj);
    }

    bool pop()
    {
        if (objects.empty())
        {
            return false;
        }
        objects.pop_back();
        return true;
    }

    T *peek()
    {
        if (objects.empty())
        {
            return nullptr;
        }
        return &objects.back();
    }

    void clear()
    {
        objects.clear();
    }

    size_t size()
    {
        return objects.size();
    }
};
