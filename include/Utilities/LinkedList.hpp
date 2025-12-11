#pragma once
// Simple educational singly linked list (template) with minimal operations.
// Using namespace as per project style (note: pollutes global scope in headers).
#include <cstddef>
#include <utility>
#include <stdexcept>
using namespace std;

template <typename T>
class LinkedList {
    struct Node { T data; Node* next; Node(T d, Node* n=nullptr): data(std::move(d)), next(n) {} };
    Node* head{nullptr};
    Node* tail{nullptr};
    size_t sz{0};
public:
    LinkedList() = default;
    ~LinkedList() { clear(); }

    LinkedList(const LinkedList& other) { for (Node* cur = other.head; cur; cur = cur->next) push_back(cur->data); }
    LinkedList& operator=(const LinkedList& other) { if (this!=&other) { clear(); for (Node* cur=other.head; cur; cur=cur->next) push_back(cur->data); } return *this; }

    LinkedList(LinkedList&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz) { other.head=other.tail=nullptr; other.sz=0; }
    LinkedList& operator=(LinkedList&& other) noexcept { if (this!=&other){ clear(); head=other.head; tail=other.tail; sz=other.sz; other.head=other.tail=nullptr; other.sz=0; } return *this; }

    bool empty() const { return sz==0; }
    size_t size() const { return sz; }

    void push_front(T value) { Node* n = new Node(std::move(value), head); head = n; if (!tail) tail = head; ++sz; }
    void push_back(T value) { Node* n = new Node(std::move(value)); if (!tail) { head = tail = n; } else { tail->next = n; tail = n; } ++sz; }

    T& front() { if (!head) throw runtime_error("empty list"); return head->data; }
    const T& front() const { if (!head) throw runtime_error("empty list"); return head->data; }

    // Simple pop_front
    void pop_front() { if (!head) return; Node* old = head; head = head->next; delete old; --sz; if (!head) tail = nullptr; }

    // Remove first element matching predicate
    template <typename Pred>
    bool remove_if(Pred p) {
        Node* prev=nullptr; Node* cur=head; while (cur){ if (p(cur->data)) { if (prev) prev->next = cur->next; else head = cur->next; if (cur==tail) tail = prev; delete cur; --sz; return true; } prev=cur; cur=cur->next; }
        return false;
    }

    void clear() { while (head) pop_front(); }

    // Iterator (forward) minimal implementation
    class iterator {
        Node* node; public: iterator(Node* n): node(n) {} T& operator*() { return node->data; } iterator& operator++(){ node = node? node->next: nullptr; return *this; } bool operator!=(const iterator& other) const { return node!=other.node; } };

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
};
