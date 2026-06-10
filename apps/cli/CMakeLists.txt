add_executable(library_cli
    CliApp.cpp
    main.cpp
)

target_link_libraries(library_cli
    PRIVATE LibraryLib
)
