cmake_minimum_required(VERSION 3.1.0)
project(navigation)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/media/storage/qt/5.12.8/gcc_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Quick QuickWidgets Multimedia Positioning REQUIRED)
qt5_add_resources(RESOURCE_FILES navigation.qrc)

add_library(navigation SHARED
        Navigation.cpp
        Navigation.h
        Navigation_global.h
        ${RESOURCE_FILES}
)

qt5_use_modules(navigation Core Gui Widgets Quick Multimedia QuickWidgets Positioning)
target_link_libraries(navigation osmscout osmscout_client_qt osmscout_map osmscout_map_qt)
target_compile_definitions(navigation PUBLIC NAVIGATION_LIBRARY)

install(TARGETS navigation
        LIBRARY DESTINATION lib/carpi)

install(FILES stylesheets/standard.oss
        DESTINATION /var/lib/carpi/stylesheets/standard.oss)