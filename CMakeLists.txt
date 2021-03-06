cmake_minimum_required(VERSION 3.1.0)
project(carpi_qt)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "/home/insane/Qt/5.15.0/gcc_64/")

option(DEBUG "Compile for debugging environment" OFF)

if(DEBUG)
    add_compile_definitions(CARPI_DEBUG)
endif()

unset(DEBUG CACHE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Gui Widgets Network Positioning REQUIRED)

add_subdirectory(modules/SystemInfo)
add_subdirectory(modules/MusicPlayer)
add_subdirectory(modules/Navigation)
add_subdirectory(modules/Wireless)

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
        libs/UI/MainWindow/MainWindow.h

        libs/Network/Network.cpp
        libs/Network/Network.h

        libs/Manager/Manager.cpp
        libs/Manager/Manager.h

        libs/GPS/GPS.cpp
        libs/GPS/GPS.h

        libs/ISettings/ISettings.cpp
        libs/ISettings/ISettings.h

        libs/Logger/Logger.cpp
        libs/Logger/Logger.h)

target_link_libraries(carpi_qt Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Positioning)

if(DEBUG)
    add_custom_command(TARGET carpi PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/maps/ $<TARGET_FILE_DIR:carpi>)
endif()

install(TARGETS carpi_qt
        RUNTIME DESTINATION bin)

install(DIRECTORY DESTINATION /var/lib/carpi/)

install(FILES carpi.desktop
        DESTINATION /root/.config/autostart/)