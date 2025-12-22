#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <algorithm>

template <typename T>
class Array{
public:
    int capacity, intialCapacity, length;
    T *items;

    Array(int capacity = 1000){
        this->length = 0;
        this->intialCapacity = capacity;
        this->capacity = capacity;
        this->items = new T[capacity];
    };

    // Copy Constructor (for deep copy)
    Array(const Array &other) {
        this->length = other.length;
        this->initialCapacity = other.initialCapacity;
        this->capacity = other.capacity;
        this->items = new T[this->capacity];
        for (int i = 0; i < length; i++) {
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
            for (int i = 0; i < length; i++) {
                this->items[i] = other.items[i];
            }
        }
        return *this;
    }

    // Move Constructor
    Array(Array &&other) noexcept {
        this->length = other.length;
        this->initialCapacity = other.initialCapacity;
        this->capacity = other.capacity;
        this->items = other.items;

        other.items = nullptr;
        other.length = 0;
        other.capacity = 0;
    }

    // Move Assignment Operator
    Array &operator=(Array &&other) noexcept {
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
    T &operator[](int index)
    {
        validateIndex(index);
        return items[index];
    }

    // indexing for const object
    const T &operator[](int index) const
    {
        validateIndex(index);
        return items[index];
    }

    T* back(){
        if(length > 0)
            return &items[length - 1];
        return nullptr;
    }

    void append(const T &item)
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
    
    void insertAt(int index, T item)
    {
        if(index != length) 
            validateIndex(index);
        if(full()) 
            resize();

        append(item);
        for(int i = length - 1; i > index; --i){
            auto temp = items[i];
            items[i] = items[i - 1];
            items[i - 1] = temp;
        }
    }

    void removeAt(int index)
    {
        validateIndex(index);
        for(int i = index; i < length - 1; i++)
            items[i] = items[i + 1];
        pop();
    }

    int find(const T &item) const
    {
        for(int i = 0; i < length; i++)
            if (items[i] == item)
                return i;
        return -1;
    }

    void remove(const T &item){
        int index = find(item);
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

    int size() const
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
        for(int i = 0; i < length; i++)
            temp[i] = items[i];
        delete[] items;
        items = temp;
    }

    void validateIndex(int index) const
    {
        if(!(0 <= index && index <= length - 1)){
            throw out_of_range("Index out of range");
        }
    }
};