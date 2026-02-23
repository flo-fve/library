cmake_minimum_required(VERSION 3.10)
project(Library VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_CLANG_TIDY clang-tidy;-p=${CMAKE_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
