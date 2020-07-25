cmake_minimum_required(VERSION 3.1.0)
project(navigation)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Quick QuickWidgets Multimedia Positioning REQUIRED)

qt5_add_resources(RESOURCE_FILES navigation.qrc)

add_library(navigation SHARED
        Navigation.cpp
        Navigation.h
        Navigation_global.h
        ${RESOURCE_FILES}
)

target_link_libraries(navigation PUBLIC Qt5::Widgets Qt5::Quick Qt5::Multimedia Qt5::QuickWidgets Qt5::Positioning
        osmscout osmscout_client_qt osmscout_map)
target_compile_definitions(navigation PUBLIC NAVIGATION_LIBRARY)

install(TARGETS navigation
        LIBRARY DESTINATION lib/carpi)

install(FILES stylesheets/standard.oss
        DESTINATION /var/lib/carpi/stylesheets/standard.oss)