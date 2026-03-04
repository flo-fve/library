include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# For Windows (optional)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(UnitTests
    test_library.cpp
)

target_link_libraries(UnitTests
    PRIVATE
    LibraryLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTests)
