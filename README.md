# 📚 Library Management System (DSA Project)

A clear, simple, team‑friendly documentation of **what we are building** and **how** we will build it using **C++** and **basic DSA concepts**.

---

# ✅ 1. Project Overview

This project is a **console‑based Library Management System** built using **C++** and fundamental **Data Structures and Algorithms**.

The system will manage:

* Books
* Members
* Borrow/Return operations
* Searching & sorting using simple DSA methods

Storage will use simple **text files (.txt)** for persistence.

---

# ✅ 2. Core Features

### **A. Book Management**

* Add new books
* Remove books
* Update book details
* Search books (title, author, category, etc.)
* Sort books (title, year, availability)
* Display all books

### **B. Member Management**

* Add members
* Remove members
* Update profile details
* Search members
* Display all members

### **C. Borrow / Return System**

* Borrow a book
* Return a book
* Check availability
* Maintain a borrowing history log

### **D. Utility Components**

* Input validation
* Date handling
* File read/write
* Unique ID generators

---

# ✅ 3. Data Structures to Use

We will use only the DSA structures allowed:

| Component      | Data Structure                     | Why                   |
| -------------- | ---------------------------------- | --------------------- |
| Books          | `vector`, `list`, or `linked list` | Easy traversal/update |
| Members        | `vector` or `linked list`          | Simple operations     |
| Borrow Records | `queue` or `list`                  | FIFO tracking / logs  |
| Search         | Linear Search                      | Simple + allowed      |
| Sort           | Bubble Sort / Selection Sort       | DSA requirement       |
| Mapping IDs    | `map` (C++ STL)                    | Fast lookup           |

---

# ✅ 4. Storage (Text Files)

We will use **simple text files**, not SQLite.

### Why text files?

* Simpler implementation
* Fully compatible with DSA course requirements
* No external libraries
* Easy for each member to debug

### Files:

```
data/
 ├── books.txt
 ├── members.txt
 └── logs.txt
```

---

# ✅ 5. Project Structure (Folder Layout)

```
LibraryManagementSystem/
│
├── include/
│   ├── BookManager.h
│   ├── MemberManager.h
│   ├── BorrowManager.h
│   ├── DataModels.h
│   └── Utils.h
│
├── src/
│   ├── BookManager.cpp
│   ├── MemberManager.cpp
│   ├── BorrowManager.cpp
│   ├── Utils.cpp
│   └── main.cpp
│
├── data/
│   ├── books.txt
│   ├── members.txt
│   └── logs.txt
│
└── Makefile
```

---

# ✅ 6. Team Task Breakdown (6 Members)

Each member gets a balanced, well‑defined responsibility.

## **👤 Member 1 — Project Lead & System Integrator**

* Coordinates team work
* Reviews code
* Ensures all modules integrate smoothly
* Final menu system & main.cpp

## **👤 Member 2 — Book Management Module**

* Implement add/remove/update/search/sort books
* Handle book‑related file operations
* Maintain `BookManager.cpp/.h`

## **👤 Member 3 — Member Management Module**

* Implement add/remove/update/search members
* Handle member data storage
* Maintain `MemberManager.cpp/.h`

## **👤 Member 4 — Borrow & Return Module**

* Borrow/return logic
* Availability checking
* Borrow logs
* Maintain `BorrowManager.cpp/.h`

## **👤 Member 5 — Utility & Data Models**

* Create `struct Book`, `struct Member`, `struct BorrowRecord`
* Implement `Utils.cpp` (validation, date handling, ID generation)
* Ensure common functions work for all modules

## **👤 Member 6 — File Handling & Persistence**

* Design file formats and loading/saving logic
* Write reusable file I/O helpers
* Ensure data consistency across the system

---

# ✅ 7. Recommended Development Flow

### **A → B → C Approach**

### **A. Core Structures First**

1. DataModels
2. Utils
3. File handling helpers

### **B. Build Main Modules**

1. MemberManager
2. BookManager
3. BorrowManager

### **C. Final Integration**

1. main.cpp — Menu UI
2. Testing
3. Debugging & validation

---

# ✅ 8. UI Structure (Console Menu)

```
======== Library Management System ========
1. Manage Books
2. Manage Members
3. Borrow/Return
4. Exit
-------------------------------------------
```

Each submenu follows similar structure.

---

# ✅ 9. Extra (Optional) Features

* Search by multiple filters
* Sorting by various fields
* Issue date + due date
* Late fine calculation
* Export log to a file

---

# 🎯 Final Notes

* Keep the system **simple**.
* Use **text files**.
* Stick to **basic DSA algorithms**.
* Write **clean, modular C++ code**.
* Every team member has a clear job.

This documentation is ready to share as a `.md` file.
