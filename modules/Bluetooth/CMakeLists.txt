cmake_minimum_required(VERSION 3.1.0)
project(bluetooth)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(bluetooth SHARED
        Bluetooth_global.h
        Bluetooth.cpp
        Bluetooth.h
        )

target_link_libraries(bluetooth PUBLIC Qt5::Widgets)
target_compile_definitions(bluetooth PUBLIC BLUETOOTH_LIBRARY)

install(TARGETS bluetooth
        LIBRARY DESTINATION lib)
