#pragma once
#include <stdexcept>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;

    Node(const T &data)
    {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class Queue
{
private:
    Node<T> *head{nullptr};
    Node<T> *tail{nullptr};
    size_t size{0};

public:
    Queue() = default;
    ~Queue() { clear(); }

    bool empty() const
    {
        return size == 0;
    }
    size_t size() const
    {
        return size;
    }

    void enqueue(const T &value)
    {
        Node<T> *temp = new Node<T>(value);
        if (!tail)
        {
            head = tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
        ++size;
    }

    T dequeue()
    {
        if (!head)
            throw runtime_error("empty queue");

        T value = head->data;
        Node<T? *temp = head;
        head = head->next;
        delete temp;
        --size;
        if (!head)
        {
            tail = nullptr;
        }
        return value;
    }

    T peek() const
    {
        if (!head)
            throw runtime_error("empty queue");
        return head->data;
    }

    void clear()
    {
        while (head)
            dequeue();
    }
};
