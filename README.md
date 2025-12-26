# 📚 Library Management System (C++ • DSA)

Console-based Library Management System showcasing fundamental Data Structures and Algorithms with a clean, layered C++ design.

— Current branch: feature/starter • Build system: CMake • C++17

## Key Features
*   **Book Management**: Add, remove, update, and search books using fast indexing.
*   **Patron Management**: Register members and track their borrowing history.
*   **Loan System**: Borrow and return books with automated due dates and fine calculations.
*   **Advanced Search/Sort**: Search by title/author and sort by year/title using custom algorithms.
*   **Persistence**: All data is saved to and loaded from text files.

## Quick Start

Prerequisites
- CMake 3.15+
- C++17 toolchain (MSVC, Clang, or GCC)

Configure & build
```bash
cmake -S . -B build
# Single-config generators (Ninja/Makefiles):
cmake --build build
# Multi-config generators (Visual Studio):
cmake --build build --config Release
```

Run
- Windows (MSVC): `build/Release/lms.exe` (or `build/Debug/lms.exe`)
- Single-config: `build/lms`

## What’s Included
- Book, Patron, Transaction models with `serialize()/deserialize()`
- Managers for books, patrons, transactions
- Core services: `LibraryController`, `LoanService`
- Console UI: `ConsoleInterface` + `UiHelpers`
- Custom DSA: HashTable, MergeSort, Array, Deque, Queue, Stack

See docs/architecture.md for the layered design.

## Project Layout
```
root/
├── include/      # Headers
│   ├── core/     # DataStore, LibraryController, LoanService
│   ├── dsa/      # HashTable, MergeSort, Array, etc.
│   ├── managers/ # BookManager, PatronManager, TransactionManager
│   ├── models/   # Book, Patron, Transaction
│   ├── ui/       # ConsoleInterface, Menus, UiHelpers
│   └── utils/    # formatting.hpp, utils.hpp
├── src/          # Source files (implementations)
│   ├── core/
│   ├── managers/
│   ├── models/
│   ├── ui/
│   └── utils/
├── data/         # Default data storage location
│   ├── books.txt
│   ├── patrons.txt
│   └── transactions.txt
├── docs/         # Project documentation
│   └── architecture.md
├── tests/        # Test files
└── CMakeLists.txt
```

## Persistence
The app uses plain text files (CSV-like) for storage. Each line is one record; fields are pipe '|' separated and written by each model’s `serialize()`.

Default data folder (recommended): `data/`
- Books: `data/books.txt` → fields: Title, Author, ISBN, Edition, PublicationYear, Category, Available(1|0), BorrowCount
- Patrons: `data/patrons.txt` → fields: ID, Name, Contact, MembershipDate, Borrowed(1|0), BorrowCount
- Transactions: `data/transactions.txt` → fields: TransactionID, BookID, PatronID, BorrowDate, DueDate, ReturnDate, Returned(1|0)

Notes
- Paths are configurable by managers/controllers; `data/` is a project-level default.
- File creation should be handled by DataStore; create `data/` if missing.
- Dates use `YYYY-MM-DD` strings; lexicographic comparisons assume this format.

## Development Status

The project is structured in the following phases:

### Phase 1: Foundation (Completed)
*   Custom DSA in place: `Deque`, `Stack`, `Queue`, `MergeSort`, `HashTable`.

### Phase 2: Management & Search (Completed)
*   Implementation of `BookManager` and `PatronManager` logic.
*   `DataStore` can serialize/deserialize objects to files.

### Phase 3: Business Rules (In Progress)
*   Complete `LoanService` borrowing/returning logic.
*   Implement overdue tracking and fine calculation using `Transaction::calculateFine(dailyRate)`.

### Phase 4: UI & Integration (In Progress)
*   Connect all menu options in `ConsoleInterface`.
*   Add input validation (preventing crashes on bad input).
*   Finalize the "Main Loop" in `main.cpp`.


## Contributing
- Headers in `include/`, implementations in `src/`
- Prefer project DSAs over STL where provided (`include/dsa`)
- Small PRs, build locally with CMake before pushing.

## License
See LICENSE.
