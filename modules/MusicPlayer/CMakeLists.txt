cmake_minimum_required(VERSION 3.1.0)
project(musicplayer)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

add_library(musicplayer SHARED
        MusicPlayer.cpp
        MusicPlayer.h
        MusicPlayer_global.h

        Player/Player.cpp
        Player/Player.h
        Player/player.ui

        Library/Library.cpp
        Library/Library.h

        Library/SongItem/SongItem.cpp
        Library/SongItem/SongItem.h

        Library/AlbumItem/AlbumItem.cpp
        Library/AlbumItem/AlbumItem.h

        Library/ListItemWithPath/ListItemWithPath.cpp
        Library/ListItemWithPath/ListItemWithPath.h
)


target_link_libraries(musicplayer PUBLIC Qt5::Widgets Qt5::Multimedia)
target_compile_definitions(musicplayer PUBLIC MUSICPLAYER_LIBRARY)

install(TARGETS musicplayer
        LIBRARY DESTINATION lib/carpi)
