#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Stack{
private:
    vector<T> objects;

public:
    Stack() = default;

    void append(T obj){
        objects.push_back(obj);
    }

    void pop(){
        objects.pop_back();
    }

    void clear(){
        objects.clear();
    }

    size_t size(){
        return objects.size();
    }
};




