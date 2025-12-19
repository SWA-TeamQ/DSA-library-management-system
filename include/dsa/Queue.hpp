#pragma once
#include <iostream>
#include "Deque.hpp"
using namespace std;

template <typename T>
class Queue
{
private:
    Deque<T> deque;

public:
    Queue() = default;
    ~Queue() { clear(); }

    bool isEmpty() const
    {
        return deque.isEmpty();
    }
    size_t size() const
    {
        return deque.size();
    }

    void enqueue(const T &value)
    {
        deque.push_back(value);
    }

    bool dequeue()
    {
        return deque.pop_front();
    }

    T *peek() const
    {
        return deque.front();
    }

    void clear()
    {
        deque.clear();
    }

    void print(){
        deque.print();
    }
};
