add_executable(library_cli
    main.cpp
)

target_link_libraries(library_cli
    PRIVATE LibraryLib
)
