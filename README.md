## carpi
## currently under development
just another raspberry pi infotainment system<br>
<b>not field tested yet</b>
<br>
### how to build
```
mkdir build ; cd build ; cmake .. -DANDROID=OFF ; make -j $(nproc) 
```
### features
#### done
- Dashboard
    - Speed-o-meter
- Media Players
    - Music
    - Video
- Navigation
    - Map
    - Search Address
    - Routing
    - Long tap to display popup with address info
#### todo
- Dashboard
    - Small
        - Map w/ current route
        - Music Player
- Media
    - Music Player polishing
    - Video Player input selector
- Navigation
    - Speed Cameras
    - Show next turns w/ distance
    - Show max speed for street
    - Stop routing when arrived
- Wireless scanning
    - Bluetooth
    - WiFi 
- Settings