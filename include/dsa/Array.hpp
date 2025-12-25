#pragma once
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename T>
class Array{
public:
    size_t capacity, initialCapacity, length;
    T *items;

    Array(size_t capacity = 1000){
        this->length = 0;
        this->initialCapacity = capacity;
        this->capacity = capacity;
        this->items = new T[capacity];
    };

    // Copy Constructor (for deep copy)
    Array(const Array &other) {
        this->length = other.length;
        this->initialCapacity = other.initialCapacity;
        this->capacity = other.capacity;
        this->items = new T[this->capacity];
        for (size_t i = 0; i < length; i++) {
            this->items[i] = other.items[i];
        }
    }

    // Copy Assignment Operator ( '=' operator overloading) // to make it work with out class objects
    Array &operator=(const Array &other) {
        if (this != &other) {
            delete[] items;
            this->length = other.length;
            this->initialCapacity = other.initialCapacity;
            this->capacity = other.capacity;
            this->items = new T[this->capacity];
            for (size_t i = 0; i < length; i++) {
                this->items[i] = other.items[i];
            }
        }
        return *this;
    }

    // Move Constructor
    Array(Array &&other) {
        this->length = other.length;
        this->initialCapacity = other.initialCapacity;
        this->capacity = other.capacity;
        this->items = other.items;

        other.items = nullptr;
        other.length = 0;
        other.capacity = 0;
    }

    // Move Assignment Operator
    Array &operator=(Array &&other) {
        if (this != &other) {
            delete[] items;
            this->length = other.length;
            this->initialCapacity = other.initialCapacity;
            this->capacity = other.capacity;
            this->items = other.items;

            other.items = nullptr;
            other.length = 0;
            other.capacity = 0;
        }
        return *this;
    }

    ~Array(){
        if (items) {
            delete[] items;
        }
    }

    // indexing
    T &operator[](size_t index)
    {
        validateIndex(index);
        return items[index];
    }

    T* begin(){
        return items;
    }

    T* end(){
        return items + length;
    }

    T* back(){
        if(length > 0)
            return &items[length - 1];
        return nullptr;
    }

    void append(T item)
    {
        if(full()) 
            resize();
        items[length++] = item;
    }

    void pop()
    {
        if(!empty())
            length--;
    }
    
    void insertAt(size_t index, T item)
    {
        if(index != length) 
            validateIndex(index);
        if(full()) 
            resize();

        append(item);
        for(size_t i = length - 1; i > index; --i){
            auto temp = items[i];
            items[i] = items[i - 1];
            items[i - 1] = temp;
        }
    }

    void removeAt(size_t index)
    {
        validateIndex(index);
        for(size_t i = index; i < length - 1; i++)
            items[i] = items[i + 1];
        pop();
    }

    size_t find(T &item)
    {
        for(size_t i = 0; i < length; i++)
            if (items[i] == item)
                return i;
        return -1;
    }

    void remove(T item){
        size_t index = find(item);
        if (index != -1)
            removeAt(index);
    }


    // Helper functions

    bool empty() const
    {
        return length == 0;
    }

    bool full() const
    {
        return length == capacity;
    }

    size_t size() const
    {
        return length;
    }

    void clear()
    {
        length = 0;
        capacity = initialCapacity;
        delete[] items;
        items = new T[capacity];
     }

    void resize(){
        capacity = capacity * 2;
        T *temp = new T[capacity];
        for(size_t i = 0; i < length; i++)
            temp[i] = items[i];
        delete[] items;
        items = temp;
    }

    void validateIndex(size_t index) const
    {
        if(!(0 <= index && index <= length - 1)){
            throw out_of_range("Index out of range");
        }
    }
};