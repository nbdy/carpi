cmake_minimum_required(VERSION 3.16)
project(carpi_qt)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(modules/SystemInfo)
add_subdirectory(modules/MusicPlayer)
add_subdirectory(modules/Navigation)

add_executable(
        carpi_qt

        main.cpp

        libs/Utils/Utils.cpp
        libs/Utils/Utils.h

        libs/ModuleLoader/ModuleLoader.cpp
        libs/ModuleLoader/ModuleLoader.h

        libs/UI/VTabWidget/VTabWidget.cpp
        libs/UI/VTabWidget/VTabWidget.h

        libs/UI/VTabBar/VTabBar.cpp
        libs/UI/VTabBar/VTabBar.h

        libs/UI/MainWindow/MainWindow.cpp
        libs/UI/MainWindow/MainWindow.h)

target_link_libraries(carpi_qt Qt5::Widgets)

install(TARGETS carpi_qt
        RUNTIME DESTINATION bin)
