cmake_minimum_required(VERSION 3.0.0)
project(carpi)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wno-enum-compare")


option(CARPI_DESKTOP "Compile desktop variant" OFF)
option(CARPI_DEBUG "Build debug variant" ON)
option(CARPI_MODULES "Build the modules" OFF)

if(CARPI_DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
else()
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(SUPPORT_CAMERA_SYSTEM OFF)
set(SUPPORT_VR_SIMULATOR OFF)
set(SUPPORT_FILEFORMAT_FLAC ON)
set(SUPPORT_SAVE_BMP ON)

set(WITH_PIC ON)
set(BUILD_SHARED_LIBS ON)

if(NOT CARPI_DESKTOP)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)
    add_definitions(-DPLATFORM=PLATFORM_DRM)
endif()

include_directories(src)
include_directories(src/ext)
include_directories(src/ext/raygui/src)

add_executable(carpi main.cpp src/carpi_config.h src/Module/Module.cpp)

link_directories(
        ${PROJECT_SOURCE_DIR}/ext/raylib/build/raylib/
)

if(CARPI_DESKTOP)
    target_link_libraries(carpi dl pthread m raylib)
    add_compile_definitions(carpi CARPI_DESKTOP)
else()
    include_directories(
            /opt/vc/lib
            /opt/vc/include
            /opt/vc/include/interface/vmcs_host/linux
            /opt/vc/include/interface/vcos/pthreads
    )
    link_directories(
            /usr/local/lib
            /opt/vc/lib
    )
    target_link_libraries(carpi dl pthread m rt stdc++fs raylib
            -L/opt/vc/lib/libbcm_host.so -L/opt/vc/lib/libbrcmEGL.so -L/opt/vc/lib/libbrcmGLESv2.so)
endif()

if(CARPI_MODULES)
    add_subdirectory(modules)
endif()
