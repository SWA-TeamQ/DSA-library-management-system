cmake_minimum_required(VERSION 3.15)
project(LibraryManagementSystem VERSION 0.1.0 LANGUAGES CXX)

# Emit build artifacts (executables/libraries/archives) directly into the project root
# so the produced .exe is placed in the repository root folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Per-config outputs for multi-config generators (Visual Studio / MSVC)
foreach(OUTPUTCONFIG IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_SOURCE_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_SOURCE_DIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_SOURCE_DIR})
endforeach()

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
    src/ui/Schemas.cpp
    src/ui/BorrrowMenu.cpp
)

# Ensure target-level properties also point to project root (per-config)
set_target_properties(lms PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}
)
