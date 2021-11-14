# Navigation
This module draws a map to the module view

## PostGIS setup
```shell
# should be executed in screen or a tmux session
# takes ~8 hours with a 500 MB file (rpi 3)
# takes ~49 hours with a 3GB file (rpi 3)
# script postgresql-username file-to-import
./scripts/postgis.sh postgres osm_files/europe-latest.osm.pbf
```
