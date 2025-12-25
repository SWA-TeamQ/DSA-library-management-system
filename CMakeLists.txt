cmake_minimum_required(VERSION 3.15)
project(LibraryManagementSystem VERSION 0.1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

include_directories(include)

add_executable(lms
    src/main.cpp
    src/models/Book.cpp
    src/models/Patron.cpp
    src/models/Transaction.cpp
    src/core/LibraryController.cpp
    src/core/LoanService.cpp
    src/managers/BookManager.cpp
    src/managers/PatronManager.cpp
    src/managers/TransactionManager.cpp
    src/utils/utils.cpp
    src/ui/ConsoleInterface.cpp
    src/ui/BookMenu.cpp
    src/ui/PatronMenu.cpp
    src/ui/TransactionMenu.cpp
    src/ui/UiHelpers.cpp
    src/ui/UiComponents.cpp
)

# Future: tests target
# enable_testing()
# add_executable(lms_tests tests/basic_tests.cpp)
# add_test(NAME lms_basic COMMAND lms_tests)
