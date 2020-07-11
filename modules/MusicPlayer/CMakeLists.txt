cmake_minimum_required(VERSION 3.16)
project(musicplayer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(musicplayer SHARED
        MusicPlayer.cpp
        MusicPlayer.h
        MusicPlayer_global.h)

target_link_libraries(musicplayer PUBLIC Qt5::Widgets)
target_compile_definitions(musicplayer PUBLIC MUSICPLAYER_LIBRARY)

install(TARGETS musicplayer
        LIBRARY DESTINATION lib)
