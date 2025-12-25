#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;
    Node(T &data)
    {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class Deque
{
private:
    Node<T> *head;
    Node<T> *tail;
    size_t length = 0;

public:
    Deque()
    {
        head = tail = nullptr;
    }
    ~Deque()
    {
        clear();
    }

    bool isEmpty() const
    {
        return length == 0;
    }

    size_t size() const
    {
        return length;
    }

    T *front() const
    {
        if (isEmpty())
        {
            return nullptr;
        }
        return &head->data;
    }

    T *back() const
    {
        if (isEmpty())
        {
            return nullptr;
        }
        return &tail->data;
    }

    void push_front(T &value)
    {
        Node<T> *node = new Node<T>(value);
        if (isEmpty())
        {
            head = tail = node;
        }
        else
        {
            node->next = head;
            head->prev = node;
            head = node;
        }
        length++;
    }

    void push_back(T &value)
    {
        Node<T> *node = new Node<T>(value);
        if (isEmpty())
        {
            head = tail = node;
        }
        else
        {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        length++;
    }

    bool pop_front()
    {
        if (isEmpty())
            return false;

        Node<T> *temp = head;
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        else
        {
            head->prev = nullptr;
        }
        length--;
        delete temp;
        return true;
    }

    bool pop_back()
    {
        if (isEmpty())
        {
            return false;
        }
        Node *temp = tail;
        tail = tail->prev;
        if (tail == nullptr)
        {
            head = nullptr;
        }
        else
        {
            tail->next = nullptr;
        }
        length--;
        delete temp;
        return true;
    }

    void print() const
    {
        if (isEmpty())
        {
            cout << "Empty list " << endl;
            return;
        }

        Node<T> *temp = head;
        while (temp)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }

    Node<T> *getHead() const
    {
        return head;
    }

    void clear()
    {
        Node<T> *current = head;
        while (current)
        {
            Node<T> *temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        length = 0;
    }
};
