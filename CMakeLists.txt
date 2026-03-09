cmake_minimum_required(VERSION 3.20)
project(Library VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ========================
# Library
# ========================

add_library(LibraryLib
    src/Library.cpp
    src/Book.cpp
    src/utils.cpp
)

target_include_directories(LibraryLib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ========================
# Applications
# ========================

add_subdirectory(apps/cli)

option(BUILD_GUI "Build Qt GUI" ON)

if(BUILD_GUI)
    add_subdirectory(apps/gui)
endif()

# ========================
# Tests
# ========================

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
