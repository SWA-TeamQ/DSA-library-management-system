# 📚 Library Management System (C++)

**A Data Structures & Algorithms (DSA) Project for Managing Library Operations**

# Library Management System (C++) — Focused DSA Version

## Overview

This repository contains a console-based Library Management System implemented in C++. The primary purpose is educational: demonstrate how core Data Structures and Algorithms (DSA) solve real-world problems.

This cleaned-up version focuses on the essentials for a DSA project and removes over-engineered features.

## Terminology

"Patron" = library user / member (a person who borrows books).

## Must-have features (minimal scope)

-   Book management: add / update / delete books (title, author, ISBN, category, availability).
-   Patron management: register patrons, prevent duplicate IDs, track current borrowed items.
-   Borrow/Return: borrow a book, return a book, update availability.
-   Waitlist: FIFO queue for unavailable books.
-   Borrowing history: per-patron history (linked list or simple vector), used for reports.
-   Popularity report: most-borrowed (heap or sort).
-   Console UI: clear menus and input validation.
-   Manual DSA implementations: linked list, queue, hash table (educational code).

## Good-to-have (optional extensions)

-   Simple file-based persistence (save/load text files).
-   Search by multiple fields (title, author, ISBN).
-   Unit tests for the data structures and controller.

## What is unnecessary for the core DSA project

-   AVL or balanced trees (overkill for this scope).
-   Full transaction logs with timestamps (a simple borrow history suffices).
-   Fines, multi-branch support, advanced roles/authentication.

## Missing but important sections (added to README)

1. Error handling & validation

    - Invalid input: provide clear messages.
    - Prevent duplicates (ISBN, Patron ID).
    - Handle missing items (book not found, empty waitlist).

2. Memory management notes

    - Explain ownership patterns used (where we allocate/free).
    - Mention destructors in custom DS implementations and importance of clearing nodes.

3. Complexity analysis (short)
    - Hash table lookup/insert/erase: average O(1), worst-case O(n).
    - Linked list insert/pop: O(1) at head/tail; search O(n).
    - Queue enqueue/dequeue: O(1).
    - Heap operations (for popularity): O(log n) per update; building report O(n log n) or O(n) with heapify.

## Build & run (Windows / pwsh)

Install CMake and a C++ compiler (MinGW or MSVC). From project root:

```pwsh
mkdir build
cd build
cmake ..
cmake --build . --config Release
./lms.exe
```

## What I changed in the codebase (short)

-   Added input validation and duplicate checks when adding books and patrons.
-   `addBook` and `addPatron` now return success flags so the UI can inform the user.
-   README trimmed and focused on DSA essentials; added memory and complexity notes.

## Next recommended steps

1. Add unit tests for `LinkedList`, `Queue`, and `BookHashTable`.
2. Implement the popularity heap and wire a "Reports" menu option.
3. (Optional) Add file-based persistence for basic save/load.

If you want, I can do any of those next: add tests, implement the heap/report, or add persistence. Which would you like me to take on now?

---

Updated: cleaned scope and added essential validation/documentation.

1. Compile the program (assuming all files are in one folder):
