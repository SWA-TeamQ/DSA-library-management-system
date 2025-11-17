# 📚 Library Management System (C++)

**A Data Structures & Algorithms (DSA) Project for Managing Library Operations**

---

## 📌 Overview

This **Library Management System** is a C++ console application designed to demonstrate the practical application of key Data Structures and Algorithms (DSA) concepts in a real-world scenario. Built entirely using core C++ and standard libraries, this system simulates the essential functions of a small library — managing books, tracking borrowers, and organizing data efficiently.

This project was developed by 3rd-year Software Engineering students at Addis Ababa Science and Technology University as part of their DSA coursework. It serves as both a learning tool and a practical demonstration of how abstract data structures solve concrete problems.

> ✅ Perfect for students learning DSA — see how linked lists, heaps, hashing, and queues power everyday systems!

---

## 🎯 Purpose & Goals

Libraries need to manage large volumes of data — books, users, loans, and waitlists — efficiently. This project aims to:

- Model library operations using fundamental DSA techniques.
- Provide hands-on experience with **linked lists**, **heaps**, **hashing**, and **queues**.
- Reinforce algorithmic thinking through practical implementation.
- Build a functional system that demonstrates **time and space complexity trade-offs**.

### Key Objectives:
- Implement book management (insert, delete, update) using appropriate data structures.
- Enable fast book search via **binary search** or **hashing**.
- Manage borrower history using a **linked list**.
- Handle waitlists using a **queue**.
- Sort books by popularity using a **max-heap** or sorting algorithm.

---

## 🔧 Features

The system supports the following core functionalities, each powered by a specific DSA concept:

| Feature | DSA Concept Used | Description |
|--------|------------------|-------------|
| **Book Insertion, Deletion, Update** | Dynamic Arrays / Linked Lists | Add, remove, or modify book records. |
| **Book Search (by Title/Author)** | Binary Search / Hashing | Quickly find books using optimized search algorithms. |
| **Waitlist Management** | Queue (FIFO) | Track users waiting for a borrowed book. |
| **Borrowing History** | Linked List | Store and display a user’s borrowing record. |
| **Book Sorting by Popularity** | Max-Heap / Sorting Algorithm | Rank books based on how often they are borrowed. |

---

## 🛠️ System Architecture

The system follows a simple, modular structure to emphasize clarity and focus on DSA:

1. **Main Menu Layer** – Console-based interface for user interaction.
2. **Data Structure Layer** – Core logic implemented using:
   - `Book` class for storing book attributes.
   - `LinkedList` for borrower history.
   - `Queue` for waitlists.
   - `Hash Table` or sorted array for fast searching.
   - `Max-Heap` or `std::sort` for popularity ranking.
3. **Utility Layer** – Helper functions for input validation, file I/O (optional), and output formatting.

> 💡 Designed for educational purposes — easy to extend or modify for deeper exploration.

---

## 🧱 Key DSA Concepts Demonstrated

This project highlights foundational DSA topics suitable for intermediate learners:

| Concept | How It's Used |
|-------|---------------|
| **Linked List** | Stores borrower history — allows dynamic insertion/deletion without fixed size limits. |
| **Queue (FIFO)** | Manages waitlists — ensures fairness by serving users in order of request. |
| **Hashing / Binary Search** | Enables O(1) or O(log n) book searches — critical for performance in large datasets. |
| **Max-Heap / Sorting** | Ranks books by popularity — demonstrates priority-based data organization. |
| **Dynamic Memory Management** | Uses pointers and manual memory allocation/deallocation (where applicable). |

These make it easier to understand how choosing the right data structure impacts efficiency and scalability.

---

## 🖥️ How to Use

### Running the System
1. Compile the program (assuming all files are in one folder):
   ```bash
   g++ -o library main.cpp Book.cpp LinkedList.cpp Queue.cpp Heap.cpp
   ```
2. Run the executable:
   ```bash
   ./library
   ```
3. Follow the menu prompts to:
   - Add, delete, or update books.
   - Search for books by title or author.
   - View borrowing history.
   - Check waitlists.
   - Sort books by popularity.

> 📝 All interactions happen through a text-based console — no GUI needed!

---

## 📁 Project Structure

```
src/
├── Book.h / Book.cpp        // Book class definition and methods
├── LinkedList.h / LinkedList.cpp  // Borrower history management
├── Queue.h / Queue.cpp      // Waitlist management (FIFO)
├── Heap.h / Heap.cpp        // For sorting books by popularity
├── main.cpp                 // Entry point with menu system
└── utils.h / utils.cpp      // Helper functions (input, display, etc.)
```

---

## 📚 Learning Value

This project is ideal for 3rd-year computer science or software engineering students because it:

- Applies classroom DSA theory to a tangible problem.
- Encourages thoughtful selection of data structures based on use case.
- Highlights trade-offs between time complexity (search speed) and space complexity (memory usage).
- Reinforces best practices in C++ programming (pointers, classes, memory management).

It’s not just code — it’s a complete system built on solid algorithmic foundations.

---

## ⚠️ Limitations

Please note:
- This is a **console-based simulation** — no graphical interface or database.
- No persistent storage (data is lost on exit unless extended).
- Simplified user roles (no admin vs. patron distinction).
- Focus is on DSA — advanced features like multi-threading or networking are out of scope.

---

## 📂 Future Improvements

Potential enhancements include:
- Adding **file persistence** (save/load library data).
- Implementing a **GUI** using SFML or Qt.
- Supporting **multiple user accounts**.
- Integrating **multi-key search** (title + author + genre).
- Visualizing data structures during operation (for debugging/learning).

---

## 🙌 Acknowledgments

Developed by:  
Abel Mekonnen, Barok Yeshiber, Betelhem Kassaye, Bemigbar Yehuwalawork, Bekam Yoseph, Amira Abdurahman  
Department of Software Engineering, Section A  
Addis Ababa Science and Technology University

Supervised by: **Abdi Muleta**

Submission Date: November 18, 2025

---

## 📚 References

- Cormen, T.H., Leiserson, C.E., Rivest, R.L., Stein, C. *Introduction to Algorithms* (4th Ed.)
- Goodrich, M.T., Tamassia, R. *Data Structures and Algorithms in C++*
- Stroustrup, B. *The C++ Programming Language* (4th Ed.)
- GeeksforGeeks, “Data Structures” & “Algorithms” sections

---

> 🔗 For more details, check out the full project documentation and diagrams:
> - [System Flow Diagram](https://lucid.app/lucidchart/.../edit) *(replace with actual link)*
> - [Class & Data Structure Relationships](https://www.mermaidchart.com/app/projects/.../diagrams/.../version/v0.1/edit) *(replace with actual link)*

---

🎓 **Think. Design. Optimize.**  
This project proves that powerful systems don’t need complex frameworks — just smart data structures and clean algorithms.
