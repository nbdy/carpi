cmake_minimum_required(VERSION 3.1.0)
project(systeminfo)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Network Positioning REQUIRED)

add_library(systeminfo SHARED
        SystemInfo_global.h
        SystemInfo.cpp
        SystemInfo.h

        ../../libs/Network/Network.cpp
        ../../libs/Network/Network.h
        ../../libs/GPS/GPS.cpp ../../libs/GPS/GPS.h)

target_link_libraries(systeminfo PUBLIC Qt5::Widgets Qt5::Network Qt5::Positioning)
target_compile_definitions(systeminfo PUBLIC SYSTEMINFO_LIBRARY)

install(TARGETS systeminfo
        LIBRARY DESTINATION lib)
