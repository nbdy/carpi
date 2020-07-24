cmake_minimum_required(VERSION 3.1.0)
project(navigation)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Quick QuickWidgets Multimedia REQUIRED)

add_library(navigation SHARED
        Navigation.cpp
        Navigation.h
        Navigation_global.h)

if(DEBUG)
    add_custom_command(TARGET navigation PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/qml/ $<TARGET_FILE_DIR:navigation>)
    add_custom_command(TARGET navigation PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/stylesheets/ $<TARGET_FILE_DIR:navigation>)
endif()

target_link_libraries(navigation PUBLIC Qt5::Widgets Qt5::Quick Qt5::Multimedia Qt5::QuickWidgets osmscout)
target_compile_definitions(navigation PUBLIC NAVIGATION_LIBRARY)

install(TARGETS navigation
        LIBRARY DESTINATION lib/carpi)
