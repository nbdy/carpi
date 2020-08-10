cmake_minimum_required(VERSION 3.5)

project(carpi_qml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick QuickControls2 Multimedia Positioning REQUIRED)

set(SOURCES main.cpp qml.qrc
        libs/Utils/IsFile/IsFile.cpp libs/Utils/IsFile/IsFile.h
        libs/Utils/CPUTemperature/CPUTemperature.cpp libs/Utils/CPUTemperature/CPUTemperature.h
        libs/Utils/Utils.h)

if(ANDROID)
    add_library(carpi_qml SHARED ${SOURCES})
else()
    add_executable(carpi_qml ${SOURCES})
endif()

target_compile_definitions(carpi_qml PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(carpi_qml
  PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2 Qt5::Multimedia Qt5::Positioning
  osmscout_client_qt osmscout_map_qt
  pthread rsettingsqt disqt tacopie)

install(TARGETS carpi_qml
        RUNTIME DESTINATION bin)

install(FILES carpi.desktop
        DESTINATION /root/.config/autostart/)