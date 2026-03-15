find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(library_gui
    main.cpp
    MainWindow.cpp
    AddBookDialog.cpp
)

qt_add_resources(library_gui "app_resources"
    PREFIX "/"
    BASE ${PROJECT_SOURCE_DIR}
    FILES
        ${PROJECT_SOURCE_DIR}/resources/style.qss
)

target_link_libraries(library_gui
    PRIVATE
        Qt6::Widgets
        LibraryLib
)

target_include_directories(library_gui
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)
