cmake_minimum_required(VERSION 3.16)
project(navigation)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(navigation SHARED
        Navigation.cpp
        Navigation.h
        Navigation_global.h)

target_link_libraries(navigation PUBLIC Qt5::Widgets)
target_compile_definitions(navigation PUBLIC NAVIGATION_LIBRARY)

install(TARGETS navigation
        LIBRARY DESTINATION lib)
