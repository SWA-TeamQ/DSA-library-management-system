# Library Management System - Project Workflow & Architecture

This document outlines the project structure, architecture, and development workflow for the **DSA-based Library Management System**. Use this as a guide to understand how the components fit together and what the final product will achieve.

---

## 1. Project Vision
The goal is to build a high-performance Library Management System (LMS) that demonstrates the practical application of **Data Structures and Algorithms (DSA)**. Unlike standard systems that rely on built-in libraries, this project prioritizes custom-built structures for efficiency and educational value.

### Key Features:
*   **Book Management**: Add, remove, update, and search books using fast indexing.
*   **Patron Management**: Register members and track their borrowing history.
*   **Loan System**: Borrow and return books with automated due dates and fine calculations.
*   **Advanced Search/Sort**: Search by title/author and sort by year/title using custom algorithms.
*   **Persistence**: All data is saved to and loaded from text files.

---

## 2. System Architecture (The "Big Picture")

The project follows a layered architecture to keep the code clean and manageable:

### Layer 1: UI (User Interface)
*   **Files**: `ConsoleInterface.cpp/hpp`
*   **Role**: Handles all user input and output. It displays menus, takes commands, and prints formatted tables.
*   **Interaction**: Only talks to the `LibraryController`.

### Layer 2: Core (Business Logic)
*   **Files**: `LibraryController.cpp/hpp`, `LoanService.cpp/hpp`
*   **Role**: The "brain" of the app. `LibraryController` coordinates between the UI and Managers. `LoanService` handles the complex rules of borrowing (e.g., checking limits, calculating fines).

### Layer 3: Managers (Data Orchestration)
*   **Files**: `BookManager.cpp/hpp`, `PatronManager.cpp/hpp`, `TransactionManager.cpp/hpp`
*   **Role**: Manages collections of data. They handle indexing (for fast search) and sorting.
*   **Interaction**: Uses `DataStore` for file I/O and `DSA` structures for in-memory storage.

### Layer 4: DSA (Data Structures & Algorithms)
*   **Files**: `include/dsa/HashTable.hpp`, `include/dsa/Deque.hpp`, `include/dsa/Stack.hpp`, `include/dsa/Queue.hpp`, `include/dsa/MergeSort.hpp`
*   **Role**: The foundation. These are custom-built containers that provide the performance for the layers above.

### Layer 5: Models (Data Entities)
*   **Files**: `Book.cpp/hpp`, `Patron.cpp/hpp`, `Transaction.cpp/hpp`
*   **Role**: Simple classes that represent a single Book, Patron, or Loan record.

---

## 3. Data Flow Example: Borrowing a Book
1.  **UI**: User selects "Borrow Book" and enters Patron ID and ISBN.
2.  **Controller**: Calls `LoanService::borrowBook(patronID, isbn)`.
3.  **LoanService**:
    *   Asks `BookManager` to find the book (uses `HashTable` for O(1) lookup).
    *   Asks `PatronManager` to find the patron.
    *   Checks if the book is available and if the patron hasn't exceeded their limit.
    *   Creates a `Transaction` object.
4.  **Managers**: Update the book's status to "unavailable" and add the transaction to the list.
5.  **DataStore**: Saves updated state to `data/books.txt`, `data/patrons.txt`, and `data/transactions.txt`.
6.  **UI**: Displays "Success! Due date is [Date]."

---

## 4. Development Roadmap (Workflow)

### Phase 1: Foundation (Current State)
*   Custom DSA in place: `Deque`, `Stack`, `Queue`, `MergeSort`, `HashTable`.

### Phase 2: Management & Search
*   Implement multi-criteria search (title/author) over `HashTable` buckets.
*   Implement `BookManager` and `PatronManager` logic.
*   Ensure `DataStore` can serialize/deserialize objects to files.

### Phase 3: Business Rules
*   Complete `LoanService` borrowing/returning logic.
*   Implement overdue tracking and fine calculation using `Transaction::calculateFine(dailyRate)`.

### Phase 4: UI & Integration
*   Connect all menu options in `ConsoleInterface`.
*   Add input validation (preventing crashes on bad input).
*   Finalize the "Main Loop" in `main.cpp`.

---

## 5. How to Contribute (For Team Members)
1.  **Check `todo.md`**: Find your assigned tasks.
2.  **Follow the Headers**: Keep your `.hpp` files in `include/` and `.cpp` files in `src/`.
3.  **Use Custom DSA**: Avoid `std::unordered_map` or `std::list` where a custom structure exists.
4.  **Test Often**: Run `cmake --build build` frequently to catch errors early.

---

## 7. Build & Run (CMake)

See README for details. Quick commands:

```bash
cmake -S . -B build
cmake --build build
# For Visual Studio generators:
cmake --build build --config Debug
```

Run the binary from `build/lms` (single-config) or `build/Debug/lms.exe` (MSVC).

Ensure a `data/` folder exists or configure paths accordingly.

---

## 6. Final End Product
A professional CLI application where a librarian can:
- Type `1` to add a book.
- Type `5` to search for a book by title (instant results via Hash Index).
- Type `8` to borrow a book (validates rules automatically).
- Exit the program and find all data safely stored in `.txt` files for the next session.
