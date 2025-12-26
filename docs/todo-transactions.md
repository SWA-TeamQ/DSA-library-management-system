# TODO: Transaction Workflow Issues

This document details logical inconsistencies and potential issues identified within the transaction workflow of the Library Management System.

## Transaction Menu (`src/ui/TransactionMenu.cpp`)

*   **Incorrect `waitForEnter()` Placement**: In `TransactionMenu::show()`, the `waitForEnter()` call for `case 3` (View all transactions) is placed *after* the `break;` statement, making it unreachable. A redundant `break;` also exists immediately after the `case 3` logic. This is a minor cosmetic bug.

## Loan Service (`src/core/LoanService.cpp`)

*   **Incomplete Rollback on Borrow Failure**:
    *   **Issue**: In `borrowBook`, if `transactionManager.addTransaction(t)` fails, the rollback for `book` and `patron` objects is incomplete. Specifically, lifetime borrow counts (`book->incrementBorrowCount()`, `patron->incrementBorrowCount()`) are not reverted.
    *   **Impact**: This can lead to inconsistent in-memory states for book and patron objects if a transaction fails to add, and these objects might not be correctly persisted if `bookManager.saveBooks()` is skipped due to the failure.
*   **Missing Patron Save After Return**:
    *   **Issue**: In `returnBook`, after a successful return, the patron's active borrow count is decremented (`patron->decrementActiveBorrowCount()`). However, `patronManager.savePatrons()` is not explicitly called afterwards.
    *   **Impact**: If the application exits before a general save operation, the patron's active borrow count might not be persisted correctly, leading to data inconsistency.
*   **Transaction ID Generation Robustness**:
    *   **Issue**: The `borrowBook` method uses `generateId("TXN")` to create transaction IDs. The robustness, uniqueness, and persistence of this ID generation mechanism across application runs need verification.
    *   **Impact**: Unreliable ID generation can lead to duplicate IDs or lost transactions.
*   **Inefficient Transaction Search in `returnBook`**:
    *   **Issue**: The `returnBook` method iterates through `transactionManager.getAllTransactions()` to find the active transaction to be returned.
    *   **Impact**: This is inefficient for large numbers of transactions. Using `TransactionManager`'s `findTransactions` method would be more performant and idiomatic.
*   **Date and Fine Calculation Accuracy**:
    *   **Issue**: The accuracy and correct implementation of `getCurrentDate()`, `addDays()`, and `Transaction::calculateFine()` (including the default `dailyRate`) need verification.
    *   **Impact**: Incorrect calculations can lead to wrong due dates, incorrect fine amounts, and user dissatisfaction.

## Transaction Manager (`include/managers/TransactionManager.hpp` & `src/managers/TransactionManager.cpp`)

*   **`removeTransaction` Exposure**: While `TransactionManager` has a `removeTransaction` method, it does not appear to be exposed through `LibraryController` or `TransactionMenu`, which is positive as it prevents accidental deletion of history. Further checks in `TransactionManager.cpp` are needed to confirm its implementation does not inadvertently allow removal.

## Library Controller (`src/core/LibraryController.cpp`)

*   **No Direct Transaction Removal**: `LibraryController` does not expose any methods that would allow for direct removal of transactions, which aligns with the requirement that transaction history should be non-removable.
*   **Transaction Listing/Searching**: Methods like `listAllTransactions`, `listTransactionsForPatron`, and `listOverdueForPatron` correctly delegate to `TransactionManager`'s find/get methods.

## General Observations

*   **Transaction History Immutability**: The workflow as observed does not allow for direct modification or deletion of completed transactions, which is desirable for historical records. The primary interaction is through creating new (borrow) or marking existing (return) transactions as complete.
