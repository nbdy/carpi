## notes

ram usage: (rpi3b+) <br>

|    tool   |                   cmd                                                                          | usage         |
|-----------|------------------------------------------------------------------------------------------------|---------------|
| osm2pgsql | osm2pgsql -c -s -C 500 -d gis bayern-latest.osm.pbf                                            | 100%          |
| osm2pgsql | osm2pgsql -c -s -C 25 -d gis bayern-latest.osm.pbf                                             | 100%          |
| imposm    | imposm --read --write --optimize -h localhost -p 5432 -U postgres -d gis bayern-latest.osm.pbf | ~25%          |

postgis table layout: <br>

 Schema |        Name        | Type  |  Owner   
:------:|:------------------:|:-----:|:--------:
 public | planet_osm_line    | table | postgres
 public | planet_osm_point   | table | postgres
 public | planet_osm_polygon | table | postgres
 public | planet_osm_roads   | table | postgres
 public | spatial_ref_sys    | table | postgres