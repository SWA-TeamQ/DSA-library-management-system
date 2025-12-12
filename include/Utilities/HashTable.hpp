#pragma once
// Simple separate chaining hash table specialized for Book keyed by ISBN.
// Educational implementation: no rehash yet (could be added later).
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include "Book.hpp"
using namespace std;

class BookHashTable
{
    struct Node
    {
        Book value;
        Node *next;
        Node(const Book &b, Node *n = nullptr) : value(b), next(n) {}
    };
    vector<Node *> buckets;
    size_t sz{0};

    size_t index(const string &key) const { return std::hash<string>{}(key) % buckets.size(); }

public:
    explicit BookHashTable(size_t capacity = 101) : buckets(capacity, nullptr) {}
    ~BookHashTable() { clear(); }

    BookHashTable(const BookHashTable &) = delete; // keep simple
    BookHashTable &operator=(const BookHashTable &) = delete;

    bool empty() const { return sz == 0; }
    size_t size() const { return sz; }

    bool insert(const Book &b)
    {
        const string &key = b.getISBN();
        size_t idx = index(key);
        Node *cur = buckets[idx];
        while (cur)
        {
            if (cur->value.getISBN() == key)
                return false;
            cur = cur->next;
        }
        buckets[idx] = new Node(b, buckets[idx]);
        ++sz;
        return true;
    }

    Book *find(const string &isbn)
    {
        size_t idx = index(isbn);
        for (Node *cur = buckets[idx]; cur; cur = cur->next)
            if (cur->value.getISBN() == isbn)
                return &cur->value;
        return nullptr;
    }

    bool erase(const string &isbn)
    {
        size_t idx = index(isbn);
        Node *cur = buckets[idx];
        Node *prev = nullptr;
        while (cur)
        {
            if (cur->value.getISBN() == isbn)
            {
                if (prev)
                    prev->next = cur->next;
                else
                    buckets[idx] = cur->next;
                delete cur;
                --sz;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    void clear()
    {
        for (auto &head : buckets)
        {
            while (head)
            {
                Node *tmp = head;
                head = head->next;
                delete tmp;
            }
        }
        sz = 0;
    }

    // Simple iteration (collect pointers)
    vector<Book *> all() const
    {
        vector<Book *> out;
        out.reserve(sz);
        for (auto head : buckets)
            for (Node *cur = head; cur; cur = cur->next)
                out.push_back(&cur->value);
        return out;
    }
};
