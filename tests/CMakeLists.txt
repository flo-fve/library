include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# For Windows (optional)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(UnitTests
    ${TEST_SOURCES}
)

target_link_libraries(UnitTests
    PRIVATE
    LibraryLib
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTests)
