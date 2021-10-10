cmake_minimum_required(VERSION 3.0.0)
project(carpi)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(carpi main.cpp config.h)
target_link_libraries(carpi ${SDL2_LIBRARIES})