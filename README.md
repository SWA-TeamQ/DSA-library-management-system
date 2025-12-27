# 📚 Library Management System (C++ • DSA)

Console-based Library Management System showcasing fundamental Data Structures and Algorithms with a clean, layered C++ design.

— Current branch: feature/starter • Build system: CMake • C++17

## Key Features
*   **Book Management**: Add, remove, update, and search books using fast indexing.
*   **Patron Management**: Register members and track their borrowing history.
*   **Loan System**: Borrow and return books with automated due dates and fine calculations.
*   **Advanced Search/Sort**: Search by title/author and sort by year/title using custom algorithms.
*   **Persistence**: All data is saved to and loaded from text files.

## Installation

Prerequisites
- CMake 3.15+
- C++17 toolchain (MSVC, Clang, or GCC)

Clone the repository:
```bash
git clone https://github.com/your-repo/dsa-library-management-system.git
cd dsa-library-management-system
```

Configure & build:
```bash
cmake -S . -B build
# For single-config generators (Ninja/Makefiles):
cmake --build build
# For multi-config generators (Visual Studio):
cmake --build build --config Release
```

## Usage

After successful installation, you can run the application:

- Windows (MSVC): `build/Release/lms.exe` (or `build/Debug/lms.exe`)
- Single-config generators (Linux/macOS): `build/lms`

Ensure the `data/` folder exists in the project root. If missing, the application will attempt to create it.

## Limitations and Non-Goals
This project is designed primarily as a demonstration of Data Structures and Algorithms in a C++ console application. As such, it has certain limitations and intentional non-goals:

-   **No GUI**: The application is strictly console-based.
-   **Basic Persistence**: Data is stored in simple text files (`.txt`). There is no integration with databases (e.g., SQL, NoSQL).
-   **Limited Error Handling**: While basic input validation is present, robust error handling for all edge cases (e.g., file corruption) is not a primary focus.
-   **No User Authentication/Roles**: The system does not include user login, authentication, or different user roles (e.g., admin, librarian, patron).
-   **Scalability**: Designed for small-to-medium datasets; not optimized for large-scale enterprise use.
-   **No Network Features**: The application does not include any network communication or remote access capabilities.

## Project Layout
Refer to `docs/architecture.md` for a detailed breakdown of the project's layered design and component responsibilities.
The top-level directory structure is as follows:
```
root/
├── include/      # Headers for various modules
├── src/          # Source files (implementations)
├── data/         # Default data storage location (text files)
├── docs/         # Project documentation (architecture.md)
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
