# Project TODOs (Delegated)

## Member 1 — Lead & UI

-   [ ] Wire load/save lifecycle: call controller.load() on startup and controller.save() on exit in [src/main.cpp](src/main.cpp) and hook into [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp) exit paths.
-   [ ] Replace placeholder menu handlers in [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp) for search/sort/remove books, search/remove patrons, view history, and data save/load.
-   [ ] Add consistent input validation/pause helpers so getline and formatted input do not conflict; centralize in UI helpers.

## Member 2 — Book Management

-   [ ] Implement book search flows by title/author and display formatted results using [src/core/LibraryController.cpp](src/core/LibraryController.cpp) and [src/managers/BookManager.cpp](src/managers/BookManager.cpp).
-   [ ] Swap current mergeSort usage with required bubble/selection sort in [src/managers/BookManager.cpp](src/managers/BookManager.cpp) for title/year sorting to meet DSA spec.
-   [ ] Implement book removal (with availability/active-loan guard) and ensure persistence/index rebuilds in [src/managers/BookManager.cpp](src/managers/BookManager.cpp) and [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp).
-   [ ] Add book update flow (title/author/category/edition/year/availability) surfaced through [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp).

## Member 3 — Patron Management

-   [ ] Implement patron search by name and update contact info; expose via [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp).
-   [ ] Implement safe removal that blocks deletion when patron has active loans (needs [src/managers/TransactionManager.cpp](src/managers/TransactionManager.cpp)).
-   [ ] Improve listing in [src/managers/PatronManager.cpp](src/managers/PatronManager.cpp) to print a formatted table with borrow counts and contact info.

## Member 4 — Borrow/Return

-   [ ] Add borrow rules: max active loans per patron, block overdue users, and compute due dates (e.g., +14 days) in [src/core/LoanService.cpp](src/core/LoanService.cpp).
-   [ ] Enhance returns: compute overdue status using dates and show fines via Transaction::calculateFine, updating [src/models/Transaction.cpp](src/models/Transaction.cpp) and messaging in [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp).
-   [ ] Implement history/overdue views for a patron in [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp) using [src/managers/TransactionManager.cpp](src/managers/TransactionManager.cpp).

## Member 5 — Utilities

-   [ ] Build real date/validation helpers in [src/utils/utils.cpp](src/utils/utils.cpp) to provide getCurrentDate, days-difference, numeric input guards, and ISBN/name validation; update [include/utils/utils.hpp](include/utils/utils.hpp).
-   [ ] Add a unique ID generator for transactions/patrons to replace time-based IDs in [src/core/LoanService.cpp](src/core/LoanService.cpp).

## Member 6 — Persistence

-   [ ] Finalize file formats and move data files into data/; update DataStore paths in managers/controllers.
-   [ ] Implement robust save/load flows in [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp) and ensure missing files are created instead of failing silently in [include/core/DataStore.hpp](include/core/DataStore.hpp).
-   [ ] Persist borrow/return state on every operation (books, patrons, transactions) and reload before UI use.

## Cross-Cutting / Bugs

-   [ ] Fix const-ref constructor mismatch in [include/core/LoanService.hpp](include/core/LoanService.hpp) so member refs are non-const; keep consistency with implementation in [src/core/LoanService.cpp](src/core/LoanService.cpp).
-   [ ] Add smoke tests or a manual checklist for add/list/search books, register patron, borrow/return with limits, and persistence.
-   [ ] Document final file formats and menu shortcuts in [README.md](README.md) once features land.
