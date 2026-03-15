find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(library_gui
    main.cpp
    MainWindow.cpp
    AddBookDialog.cpp
)

target_link_libraries(library_gui
    PRIVATE
        Qt6::Widgets
        LibraryLib
)

target_include_directories(library_gui
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)
