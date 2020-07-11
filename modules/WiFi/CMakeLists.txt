cmake_minimum_required(VERSION 3.16)
project(wifi)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(wifi SHARED
        WiFi_global.h
        WiFi.cpp
        WiFi.h
        )

target_link_libraries(wifi PUBLIC Qt5::Widgets)
target_compile_definitions(wifi PUBLIC WIFI_LIBRARY)

install(TARGETS wifi
        LIBRARY DESTINATION lib)
