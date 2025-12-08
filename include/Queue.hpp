#pragma once
// Simple educational FIFO queue using singly linked nodes.
#include <stdexcept>
#include <utility>
using namespace std;

template <typename T>
class Queue {
    struct Node { T data; Node* next; Node(T d): data(std::move(d)), next(nullptr) {} };
    Node* head{nullptr};
    Node* tail{nullptr};
    size_t sz{0};
public:
    Queue() = default;
    ~Queue() { clear(); }

    Queue(const Queue& other) { for (Node* cur=other.head; cur; cur=cur->next) enqueue(cur->data); }
    Queue& operator=(const Queue& other) { if (this!=&other){ clear(); for (Node* cur=other.head; cur; cur=cur->next) enqueue(cur->data);} return *this; }

    Queue(Queue&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz) { other.head=other.tail=nullptr; other.sz=0; }
    Queue& operator=(Queue&& other) noexcept { if (this!=&other){ clear(); head=other.head; tail=other.tail; sz=other.sz; other.head=other.tail=nullptr; other.sz=0; } return *this; }

    bool empty() const { return sz==0; }
    size_t size() const { return sz; }

    void enqueue(T value) { Node* n = new Node(std::move(value)); if (!tail) { head=tail=n; } else { tail->next = n; tail = n; } ++sz; }
    void dequeue() { if (!head) return; Node* old=head; head=head->next; delete old; --sz; if (!head) tail=nullptr; }
    T& front() { if (!head) throw runtime_error("empty queue"); return head->data; }
    const T& front() const { if (!head) throw runtime_error("empty queue"); return head->data; }

    void clear() { while(head) dequeue(); }
};
