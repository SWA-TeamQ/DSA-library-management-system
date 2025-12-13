# 📋 Team Task Classification & Assignments

Based on the comparison between the current project state and the architectural plan, here is the detailed task breakdown for each team member.

## 🛠️ Current Project Status

-   **Implemented:** Basic `Book`, `Patron`, `Transaction` classes. `LibraryController` handles basic add/find/borrow/return. `BookHashTable` used for book storage.
-   **Missing:** File persistence (saving/loading data), Advanced Search (Title/Author), Sorting (Bubble/Selection), Update/Remove logic for members, Input Validation, and modular separation.

---

## 👤 Member 1: Project Lead & System Integrator

**Role:** Coordinator & UI/UX
**Focus:** Main Menu, Integration, Code Review.

### 📝 Tasks:

1.  **Refine `ConsoleInterface.cpp`:**
    -   Update the menu to include new options: "Search Book by Title", "Sort Books", "Update Member", "Save/Load Data".
    -   Ensure the UI loops correctly and handles invalid menu inputs gracefully.
2.  **Integration:**
    -   Merge code from Member 6 (File Handling) into `main.cpp` to ensure data loads when the program starts and saves when it exits.
    -   Merge code from Members 2, 3, and 4 into the main controller.
3.  **Code Review:**
    -   Ensure Member 2 uses the required Sorting Algorithms (Bubble/Selection).
    -   Ensure Member 6's file format is consistent (e.g., CSV or pipe-separated).

---

## 👤 Member 2: Book Management Module

**Role:** Book Logic Specialist
**Focus:** Advanced Search, Sorting, Updates.

### 📝 Tasks:

1.  **Implement Search:**
    -   Add `findBooksByTitle(string title)` and `findBooksByAuthor(string author)`.
    -   _Note:_ Since Books are in a Hash Table, you will need to iterate through all buckets to find matches.
2.  **Implement Sorting (Crucial DSA Requirement):**
    -   Add `sortBooksByTitle()` and `sortBooksByYear()`.
    -   _Implementation:_ Extract all books from the Hash Table into a temporary `vector<Book>`, then apply **Bubble Sort** or **Selection Sort** to that vector and display the result.
3.  **Implement Update:**
    -   Add `updateBookDetails(string isbn, ...)` to modify title, author, or category of an existing book.

---

## 👤 Member 3: Member (Patron) Management Module

**Role:** User Management Specialist
**Focus:** Member CRUD, Search.

### 📝 Tasks:

1.  **Implement Search:**
    -   Add `findPatronByName(string name)`.
    -   _Implementation:_ Linear search through the `patrons` vector.
2.  **Implement Update:**
    -   Add `updatePatronContact(string id, string newContact)`.
3.  **Implement Remove:**
    -   Add `removePatron(string id)`.
    -   _Constraint:_ Prevent removal if the patron currently has unreturned books (check with Member 4's module).
4.  **Display:**
    -   Improve `listAllPatrons()` to show formatted table output.

---

## 👤 Member 4: Borrow & Return Module

**Role:** Transaction Specialist
**Focus:** Logic, Fines, History.

### 📝 Tasks:

1.  **Borrowing Rules:**
    -   Enforce a limit (e.g., Max 3 books per user). Check this in `borrowBook`.
    -   Prevent borrowing if the user has overdue books.
2.  **Fine Calculation:**
    -   In `returnBook`, calculate the fine using `Transaction::calculateFine()` if the book is returned late.
    -   Display the fine amount to the user upon return.
3.  **History Log:**
    -   Add `getBorrowHistory(string patronID)` to show all past and current transactions for a specific user.
    -   Add `getOverdueBooks()` to list all books currently overdue.

---

## 👤 Member 5: Utility & Data Models

**Role:** Helper Functions & Validation
**Focus:** `Utils.cpp`, Validation, Date Handling.

### 📝 Tasks:

1.  **Create `Utils.hpp` / `Utils.cpp`:**
    -   Move date handling logic here (e.g., `getCurrentDate()`, `calculateDaysDifference()`).
2.  **Input Validation:**
    -   Create functions like `isValidISBN(string)`, `isValidName(string)`.
    -   Ensure numeric inputs (like menu choices) don't crash the program if text is entered.
3.  **ID Generation:**
    -   Create a helper to generate unique Transaction IDs (e.g., `TXN-2023-001`) instead of simple counters if possible.

---

## 👤 Member 6: File Handling & Persistence

**Role:** Storage Architect
**Focus:** Reading/Writing `.txt` files.

### 📝 Tasks:

1.  **Design File Formats:**
    -   Decide on a format (e.g., `ISBN|Title|Author|Status`).
2.  **Implement `FileHandler` Class:**
    -   `saveBooks(const BookHashTable& books)`: Iterate and write all books to `data/books.txt`.
    -   `loadBooks(BookHashTable& books)`: Read from file and insert into the Hash Table.
    -   `savePatrons(const vector<Patron>& patrons)`: Write to `data/members.txt`.
    -   `loadPatrons(vector<Patron>& patrons)`: Read from file.
    -   `saveTransactions(...)` / `loadTransactions(...)`: Persist active loans and history to `data/logs.txt`.
3.  **Error Handling:**
    -   Handle cases where files don't exist (create them) or are corrupted.
