# 📚 Library Management System (C++ • DSA)

Console-based Library Management System showcasing fundamental Data Structures and Algorithms with a clean, layered C++ design.

— Current branch: feature/starter • Build system: CMake • C++17

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
include/
	core/        # DataStore, LibraryController, LoanService
	dsa/         # HashTable, MergeSort, Array, etc.
	managers/    # BookManager, PatronManager, TransactionManager
	models/      # Book, Patron, Transaction
	ui/          # ConsoleInterface, Menus, UiHelpers
	utils/       # formatting.hpp, utils.hpp
src/
	core/ managers/ models/ ui/ utils/
docs/
```

## Persistence (Option A: document here)
The app uses plain text files (CSV-like) for storage. Each line is one record; fields are comma-separated and written by each model’s `serialize()`.

Default data folder (recommended): `data/`
- Books: `data/books.txt` → fields: Title, Author, ISBN, Edition, PublicationYear, Category, Available(1|0), BorrowCount
- Patrons: `data/patrons.txt` → fields: ID, Name, Contact, MembershipDate, Borrowed(1|0), BorrowCount
- Transactions: `data/transactions.txt` → fields: TransactionID, BookID, PatronID, BorrowDate, DueDate, ReturnDate, Returned(1|0)

Notes
- Paths are configurable by managers/controllers; `data/` is a project-level default.
- File creation should be handled by DataStore; create `data/` if missing.
- Dates use `YYYY-MM-DD` strings; lexicographic comparisons assume this format.

## Build/Run Tips
- If using Visual Studio generators, always pass `--config Debug|Release` when building and choose the matching binary to run.
- Enable warnings are configured (`/W4` on MSVC, `-Wall -Wextra -pedantic` elsewhere).
- If you see missing file errors, ensure the `data/` folder exists.

## Feature Status
- Current focus (see todo.md):
	- Wire save/load on startup/shutdown
	- Borrow rules, overdue, fines via `LoanService`/`Transaction`
	- Search/sort in managers using custom DSA

More detail: docs/Task-classification.md and todo.md

## Contributing
- Headers in `include/`, implementations in `src/`
- Prefer project DSAs over STL where provided (`include/dsa`)
- Small PRs, build locally with CMake before pushing
- See workflow.md for the roadmap and integration order

## License
See LICENSE.
