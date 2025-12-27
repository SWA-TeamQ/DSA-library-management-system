# Project TODOs: Logical Inconsistencies and Data Integrity Issues

This document outlines identified logical inconsistencies and data integrity issues within the project. These are not syntax errors but rather functional or data-related flaws that need to be addressed to ensure the application's robustness and correctness.

## UI/Menu Inconsistencies

*   **Missing Required Fields Prompting**: Several UI menus (e.g., for adding/editing books, patrons, or transactions) do not consistently prompt the user to enter all required fields for the respective components. This leads to incomplete data being potentially entered or operations failing unexpectedly.
    *   **Specific areas to investigate**: Book creation/update forms, Patron registration/update forms, Transaction processing.

## Data Integrity Issues

*   **Inconsistent State Saving**: Following updates to data (e.g., after modifying book details, patron information, or transaction status), the application does not always ensure that the entire dataset is saved to its persistent storage (e.g., `.txt` files). This can lead to data loss or inconsistencies between the in-memory state and the stored state.
    *   **Specific scenario to investigate**: Ensure that after updating book information, all book records are properly serialized and saved to `data/books.txt`. Similar checks are needed for patrons and transactions.
*   **Data Validation Gaps**: While some input validation might exist, there may be logical gaps where invalid data can be entered, leading to corrupt states or unexpected behavior.
    *   **Example**: Ensure that ISBNs, dates, or numerical IDs are validated for format and logical correctness before being accepted and saved.

## Backend/Logic Interactions

*   **UI-Backend Synchronization**: There might be instances where the UI presents options or states that are not fully synchronized with the backend's current data state, leading to user confusion or incorrect actions.
    *   **Example**: A book might appear available in the UI but is marked as unavailable in the backend due to a failed save operation.
