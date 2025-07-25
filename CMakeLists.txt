cmake_minimum_required(VERSION 3.16)
project(QtWidgetsApplication1 LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SOURCE_GROUP("Resource Files")

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core network)
find_package(Qt5 COMPONENTS Core network widgets REQUIRED)
if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options("/execution-charset:utf-8")
endif()


find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()
file(GLOB res "res/*.qrc")
set(PROJECT_SOURCES
    main.cpp
    QtWidgetsApplication1.ui
    QtWidgetsApplication1.h
    QtWidgetsApplication1.cpp
    SettingsWindow.h
    SettingsWindow.cpp
    parallelportcontroller.h
    parallelportcontroller.cpp
)


add_executable(${PROJECT_NAME}  ${PROJECT_SOURCES}
    main.cpp
    ${res}
)


target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Widgets
    Qt5::Core
    Qt5::Network
)

