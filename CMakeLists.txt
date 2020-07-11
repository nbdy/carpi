project(carpi)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fpermissive -Wnarrowing")

option(rpi "RPI" AUTO)
if(RPI EQUAL "AUTO")
    if(EXISTS "/sys/firmware/devicetree/base/model")
        set(RPI ON)
    else()
        set(RPI OFF)
    endif()
endif()

if(rpi EQUAL ON)
    option(rpi "build for raspberry pi" ON)
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
else()
    option(rpi "build for raspberry pi" OFF)
endif()

add_executable(
        carpi

        main.cpp

        libs/UI/Toast/Toast.cpp
        libs/UI/Toast/Toast.h
        libs/UI/Keyboard/Key/Key.cpp
        libs/UI/Keyboard/Key/Key.h
        libs/UI/Widget/Widget.cpp
        libs/UI/Widget/Widget.h
        libs/UI/Keyboard/Row/KeyboardRow.cpp
        libs/UI/Keyboard/Row/KeyboardRow.h
        libs/UI/Keyboard/Layout/KeyboardLayout.cpp
        libs/UI/Keyboard/Layout/KeyboardLayout.h
        libs/UI/View/View.cpp
        libs/UI/View/View.h
        libs/UI/WidgetManager/WidgetManager.cpp
        libs/UI/WidgetManager/WidgetManager.h
        libs/UI/ToastManager/ToastManager.cpp
        libs/UI/ToastManager/ToastManager.h
        libs/UI/Sidebar/Sidebar.cpp
        libs/UI/Sidebar/Sidebar.h
        libs/UI/ViewManager/ViewManager.cpp
        libs/UI/ViewManager/ViewManager.h
        libs/UI/View/WithBack/ViewWithBack.cpp
        libs/UI/View/WithBack/ViewWithBack.h
        libs/UI/View/WithBackAndSettings/ViewWithBackAndSettings.cpp
        libs/UI/View/WithBackAndSettings/ViewWithBackAndSettings.h
        libs/UI/View/MusicPlayer/ViewMusicPlayer.cpp
        libs/UI/View/MusicPlayer/ViewMusicPlayer.h
        libs/UI/View/MusicPlayer/Aux/ViewAuxMusicPlayer.cpp
        libs/UI/View/MusicPlayer/Aux/ViewAuxMusicPlayer.h
        libs/UI/View/MusicPlayer/Radio/ViewRadioMusicPlayer.cpp
        libs/UI/View/MusicPlayer/Radio/ViewRadioMusicPlayer.h
        libs/UI/View/Main/ViewMain.cpp
        libs/UI/View/Main/ViewMain.h
        libs/UI/View/MainMenu/ViewMainMenu.cpp
        libs/UI/View/MainMenu/ViewMainMenu.h
        libs/UI/View/Audio/ViewAudio.cpp
        libs/UI/View/Audio/ViewAudio.h
        libs/UI/View/Wireless/ViewWireless.cpp
        libs/UI/View/Wireless/ViewWireless.h
        libs/UI/View/Wireless/HackRF/ViewWirelessHackRF.cpp
        libs/UI/View/Wireless/HackRF/ViewWirelessHackRF.h
        libs/UI/View/Settings/ViewSettings.cpp
        libs/UI/View/Settings/ViewSettings.h
        libs/UI/View/Settings/Wireless/HackRF/ViewSettingsWirelessHackRF.cpp
        libs/UI/View/Settings/Wireless/HackRF/ViewSettingsWirelessHackRF.h
        libs/UI/View/Settings/System/ViewSettingsSystem.cpp
        libs/UI/View/Settings/System/ViewSettingsSystem.h
        libs/UI/View/Wireless/Template/ViewWirelessTemplate.cpp
        libs/UI/View/Wireless/Template/ViewWirelessTemplate.h
        libs/UI/View/Wireless/WiFi/ViewWirelessWiFi.cpp
        libs/UI/View/Wireless/WiFi/ViewWirelessWiFi.h
        libs/UI/View/Wireless/Bluetooth/ViewWirelessBluetooth.cpp
        libs/UI/View/Wireless/Bluetooth/ViewWirelessBluetooth.h
        libs/UI/View/Settings/GPS/ViewSettingsGPS.cpp
        libs/UI/View/Settings/GPS/ViewSettingsGPS.h
        libs/UI/View/Settings/Wireless/ViewSettingsWireless.cpp
        libs/UI/View/Settings/Wireless/ViewSettingsWireless.h
        libs/UI/View/Settings/Audio/ViewSettingsAudio.cpp
        libs/UI/View/Settings/Audio/ViewSettingsAudio.h
        libs/UI/View/Settings/UI/ViewSettingsUI.cpp
        libs/UI/View/Settings/UI/ViewSettingsUI.h
        libs/UI/View/Map/ViewMap.cpp
        libs/UI/View/Map/ViewMap.h
        libs/UI/View/Settings/Map/ViewSettingsMap.cpp
        libs/UI/View/Settings/Map/ViewSettingsMap.h
        libs/UI/View/Settings/Map/Cache/ViewSettingsMapCache.cpp
        libs/UI/View/Settings/Map/Cache/ViewSettingsMapCache.h
        libs/UI/View/Settings/Map/Download/ViewSettingsMapDownload.cpp
        libs/UI/View/Settings/Map/Download/ViewSettingsMapDownload.h
        libs/UI/View/Settings/Wireless/WiFi/ViewSettingsWirelessWiFi.cpp
        libs/UI/View/Settings/Wireless/WiFi/ViewSettingsWirelessWiFi.h
        libs/UI/View/Settings/Wireless/Bluetooth/ViewSettingsWirelessBluetooth.cpp
        libs/UI/View/Settings/Wireless/Bluetooth/ViewSettingsWirelessBluetooth.h
        libs/UI/View/Settings/Audio/Aux/ViewSettingsAudioAux.cpp
        libs/UI/View/Settings/Audio/Aux/ViewSettingsAudioAux.h
        libs/UI/View/Settings/Audio/Radio/ViewSettingsAudioRadio.cpp
        libs/UI/View/Settings/Audio/Radio/ViewSettingsAudioRadio.h
        libs/UI/View/Settings/Audio/Library/ViewSettingsAudioLibrary.cpp
        libs/UI/View/Settings/Audio/Library/ViewSettingsAudioLibrary.h
        libs/UI/View/FileManager/ViewFileManager.cpp
        libs/UI/View/FileManager/ViewFileManager.h
        libs/UI/View/Updater/ViewUpdater.cpp
        libs/UI/View/Updater/ViewUpdater.h
        libs/UI/View/Settings/Updater/ViewSettingsUpdater.cpp
        libs/UI/View/Settings/Updater/ViewSettingsUpdater.h
        libs/UI/View/Settings/FileManager/ViewSettingsFileManager.cpp
        libs/UI/View/Settings/FileManager/ViewSettingsFileManager.h

        libs/Runnable/Runnable.cpp
        libs/Runnable/Runnable.h
        libs/Manager/Manager.cpp
        libs/Manager/Manager.h
        libs/GPS/GPS.cpp
        libs/GPS/GPS.h
        libs/Timestamp/Timestamp.cpp
        libs/Timestamp/Timestamp.h
        libs/Network/Network.cpp
        libs/Network/Network.h
        libs/Utils/Utils.cpp
        libs/Utils/Utils.h
        libs/MusicLibrary/MusicLibrary.cpp
        libs/MusicLibrary/MusicLibrary.h
        libs/FMTX/FMTX.cpp
        libs/FMTX/FMTX.h
        libs/SpectrumPaint/SpectrumPaint.cpp
        libs/SpectrumPaint/SpectrumPaint.h
        libs/Configuration/Configuration.cpp
        libs/Configuration/Configuration.h
        libs/MusicPlayer/MusicPlayer.cpp
        libs/MusicPlayer/MusicPlayer.h
        libs/WifiScanner/WifiScanner.cpp
        libs/WifiScanner/WifiScanner.h
        libs/Device/Device.cpp
        libs/Device/Device.h
        libs/Navigation/Navigation.cpp
        libs/Navigation/Navigation.h
        libs/Updater/Updater.cpp
        libs/Updater/Updater.h
        libs/BluetoothScanner/BluetoothScanner.cpp
        libs/BluetoothScanner/BluetoothScanner.h
        libs/Command/Command.cpp
        libs/Command/Command.h
        libs/MBTiles/MBTiles.cpp
        libs/MBTiles/MBTiles.h
        libs/HackRF/HackRF.cpp
        libs/HackRF/HackRF.h
        libs/Subprocess/Subprocess.cpp
        libs/Subprocess/Subprocess.h
        libs/PostgreSQLDB/PostgreSQLDB.cpp
        libs/PostgreSQLDB/PostgreSQLDB.h

        libs/cppGzip/DecodeGzip.cpp
        libs/cppGzip/DecodeGzip.h
        libs/cppGzip/EncodeGzip.cpp
        libs/cppGzip/EncodeGzip.h
        libs/cppGzip/HandleDeflate.h

        libs/mbtiles-cpp/MBTileReader/MBTileReader.cpp
        libs/mbtiles-cpp/MBTileReader/MBTileReader.h
        libs/mbtiles-cpp/vector_tile21/vector_tile.pb.cc
        libs/mbtiles-cpp/vector_tile21/vector_tile.pb.h
        libs/mbtiles-cpp/VectorTile/VectorTile.cpp
        libs/mbtiles-cpp/VectorTile/VectorTile.h

        raygauge/libs/Circle/Circle.cpp
        raygauge/libs/Circle/Circle.h

        libs/raygui/raygui.h
        libs/raygui/ricons.h
)

include(FindProtobuf)

target_link_libraries(carpi pthread curl sndfile ao gps sqlite3 z bz2 expat mpg123 bluetooth icuuc pq)
target_link_libraries(carpi raylib tins mapnik)

if(rpi)
    target_link_libraries(carpi brcmEGL rt bcm_host brcmGLESv2)
else()
    target_link_libraries(carpi X11)
endif(rpi)

target_include_directories(carpi PUBLIC ${Protobuf_INCLUDE_DIR})

target_link_libraries(carpi ${PROTOBUF_LIBRARIES} dl)

install(DIRECTORY DESTINATION "/var/lib/carpi")
install(DIRECTORY DESTINATION "/var/lib/carpi/icons")
install(DIRECTORY DESTINATION "/var/lib/carpi/map")
install(DIRECTORY DESTINATION "/var/lib/carpi/map/pbf")
install(DIRECTORY DESTINATION "/var/lib/carpi/map/cache")
install(DIRECTORY DESTINATION "/var/lib/carpi/database")

install(TARGETS carpi
        RUNTIME DESTINATION bin)

install(FILES config.json mapnik.xml
        DESTINATION /etc/carpi/
        COMPONENT config)