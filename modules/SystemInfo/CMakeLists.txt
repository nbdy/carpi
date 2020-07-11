cmake_minimum_required(VERSION 3.16)
project(systeminfo)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(systeminfo SHARED
        SystemInfo_global.h
        Navigation.cpp
        SystemInfo.h
        )

target_link_libraries(systeminfo PUBLIC Qt5::Widgets)
target_compile_definitions(systeminfo PUBLIC SYSTEMINFO_LIBRARY)

install(TARGETS systeminfo
        LIBRARY DESTINATION lib)
