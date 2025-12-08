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
    src/Book.cpp
    src/Patron.cpp
    src/Transaction.cpp
    src/LibraryController.cpp
    src/ConsoleInterface.cpp
)

# Future: tests target
# enable_testing()
# add_executable(lms_tests tests/basic_tests.cpp)
# add_test(NAME lms_basic COMMAND lms_tests)
