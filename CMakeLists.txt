cmake_minimum_required(VERSION 3.10)
project(Bibliotheque VERSION 1.0 LANGUAGES CXX)

# Indispensable pour tes hooks (clang-tidy, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# On définit le standard C++ (ex: C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# On cherche tous les fichiers sources dans le dossier src/
file(GLOB SOURCES "src/*.cpp")

# On définit l'exécutable à produire
add_executable(main ${SOURCES})

# L'équivalent de ton "-I ./include"
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
