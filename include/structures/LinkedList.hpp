#pragma once
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T &data){
        this->data = data;
        next = nullptr;
    }
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void push_front(const T& value) {
        Node<T>* node = new Node<T>(value);
        node->next = head;
        head = node;
    }

    void push_back(const T& value) {
        Node<T>* node = new Node<T>(value);
        if (!head) {
            head = node;
            return;
        }
        Node<T>* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = node;
    }

    T pop_front() {
        if (!head) throw std::runtime_error("List empty");
        Node<T>* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        return value;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print() const {
        Node<T>* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }
};
