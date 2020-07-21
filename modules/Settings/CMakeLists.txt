cmake_minimum_required(VERSION 3.1.0)
project(settings)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(settings SHARED
        Settings_global.h
        Settings.cpp
        Settings.h
        SettingsTab/SettingsTab.cpp SettingsTab/SettingsTab.h)

target_link_libraries(settings PUBLIC Qt5::Widgets)
target_compile_definitions(settings PUBLIC SETTINGS_LIBRARY)

install(TARGETS settings
        LIBRARY DESTINATION lib/carpi)
