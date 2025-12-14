# Library Management System Architecture

## Overview
The Library Management System (LMS) is a console-based application built in C++ that demonstrates fundamental Data Structures and Algorithms (DSA) concepts. It manages library operations including book inventory, patron management, and transaction tracking for borrowing and returning books. The system uses text files for data persistence and provides a menu-driven console interface.

## System Architecture

### High-Level Design
The application follows a layered architecture with clear separation of concerns:

```
┌─────────────────┐
│   Console UI    │  ← User Interface Layer
├─────────────────┤
│ Library Controller │  ← Business Logic Layer
├─────────────────┤
│     Managers     │  ← Data Management Layer
├─────────────────┤
│     Models       │  ← Data Layer
├─────────────────┤
│   Data Store     │  ← Persistence Layer
└─────────────────┘
```

### Component Descriptions

#### 1. Models (Data Layer)
- **Book**: Represents a book with attributes like ISBN, title, author, etc.
- **Patron**: Represents a library member with ID, name, contact, etc.
- **Transaction**: Represents a borrowing transaction with IDs, dates, status.

All models implement `serialize()` and `deserialize()` methods for text file persistence.

#### 2. Managers (Data Management Layer)
- **BookManager**: Handles book CRUD operations, searching, sorting using HashTable and MergeSort.
- **PatronManager**: Manages patron data with HashTable for fast ID lookups.
- **TransactionManager**: Manages transaction records.

#### 3. LibraryController (Business Logic Layer)
Central coordinator that:
- Holds instances of all managers
- Provides unified API for operations
- Handles data loading/saving coordination

#### 4. ConsoleInterface (User Interface Layer)
- Provides menu-driven console interface
- Handles user input/output
- Delegates operations to LibraryController

#### 5. DataStore (Persistence Layer)
Generic template class for file I/O operations using serialize/deserialize.

### Data Flow

1. **Startup**: Main creates LibraryController → loads data from files via managers
2. **User Interaction**: ConsoleInterface displays menus → calls LibraryController methods
3. **Operations**: Controller delegates to appropriate manager → manager updates data structures
4. **Persistence**: Managers use DataStore to save changes to text files
5. **Shutdown**: Data automatically saved on exit

### Data Structures Used

- **HashTable**: For O(1) lookups (books by ISBN, patrons by ID)
- **Vector**: For ordered storage and iteration
- **MergeSort**: For sorting books by various criteria
- **LinkedList, Queue, Stack**: Available for future extensions

### Key Design Decisions

- **Text File Persistence**: Simple, no external dependencies
- **Console Interface**: Easy to implement, platform-independent
- **Modular Design**: Easy to maintain and extend
- **DSA Focus**: Demonstrates practical use of data structures

### File Organization
```
include/          # Headers
├── models/       # Data models
├── managers/     # Business logic
├── core/         # Controllers
├── ui/           # Interface
├── structures/   # DSA implementations
└── utils/        # Helpers

src/              # Implementations
docs/             # Documentation
```

This architecture provides a solid foundation for a library management system while effectively demonstrating DSA concepts.
