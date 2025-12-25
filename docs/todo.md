# Project TODOs (Delegated)

## Member 1 — Lead & UI Glue
- [ ] Integrate BookMenu: route ConsoleInterface book options to [src/ui/BookMenu.cpp](src/ui/BookMenu.cpp) and remove placeholder handlers in [src/ui/ConsoleInterface.cpp](src/ui/ConsoleInterface.cpp).
- [ ] Unify input handling: use one readLine/readInt helper to avoid `cin`/`getline` mix; centralize in [include/ui/UiHelpers.hpp](include/ui/UiHelpers.hpp) and apply across menus.
- [ ] Wire load/save lifecycle: call controller.load() on startup and controller.save() on exit in [src/main.cpp](src/main.cpp) and ConsoleInterface exit paths.

## Member 2 — Book Management
- [ ] Fix add-book result: make [src/core/LibraryController.cpp](src/core/LibraryController.cpp) return the real BookManager::addBook result so duplicate ISBNs are surfaced to UI.
- [ ] Add book update flow (title/author/category/edition/year/availability) and menu entry; reuse controller.updateBook.
- [ ] Guard removals: ensure BookManager remove blocks active loans (via LoanService/TransactionManager) and rebuild indices/persistence; surface messaging in UI.

## Member 3 — Patron Management
- [ ] Implement patron search by name/ID and contact update; expose via ConsoleInterface.
- [ ] Safe removal: block deletion when patron has active loans (TransactionManager/LoanService), with clear UI feedback.
- [ ] Improve listing output to a formatted table (name/contact/borrowed flag/borrowCount).

## Member 4 — Borrow/Return & History
- [ ] Add borrow rules: max active loans per patron, block overdue users, compute due dates (e.g., +14 days) in [src/core/LoanService.cpp](src/core/LoanService.cpp).
- [ ] Enhance returns: compute overdue status/fines via Transaction::calculateFine; update Transaction model and UI messaging.
- [ ] Implement transaction history/overdue views per patron in ConsoleInterface using TransactionManager.

## Member 5 — Utilities
- [ ] Add date/validation helpers in [src/utils/utils.cpp](src/utils/utils.cpp) for current date, day difference, numeric input guards, and ISBN/name validation; update headers.
- [ ] Provide unique ID generator for transactions/patrons to replace time-based IDs in LoanService.

## Member 6 — Persistence
- [ ] Finalize data file locations (e.g., data/) and update DataStore paths in managers/controllers.
- [ ] Harden save/load flows in ConsoleInterface; ensure DataStore creates missing files and reports failures.
- [ ] Verify borrow/return state persists across runs (books availability, patron borrowed flag, transactions).

## Cross-Cutting / Quality
- [ ] Fix const-ref mismatch in [include/core/LoanService.hpp](include/core/LoanService.hpp) vs implementation to keep member refs non-const.
- [ ] Add a smoke-test checklist (or minimal automated tests) covering add/list/search books, register patron, borrow/return with limits, save/load.
- [ ] Update [README.md](README.md) with menu shortcuts, data file locations, and feature status once items land.
